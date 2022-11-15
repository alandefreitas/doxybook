#include <doxybook/doxygen.hpp>
//
#include <doxybook/exception.hpp>
#include <doxybook/exception_utils.hpp>
#include <doxybook/json_converter.hpp>
#include <doxybook/text_markdown_printer.hpp>
#include <doxybook/text_plain_printer.hpp>
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <set>

using namespace doxybook;

static void
recursive_refid_print(node const& node, int const indent = 0) {
    for (auto const& child: node.get_children()) {
        if (node.get_kind() == kind::DIR || node.get_kind() == kind::FILE) {
            if (child->get_kind() != kind::DIR
                && child->get_kind() != kind::FILE)
            {
                continue;
            }
        }

        std::cout << std::string(indent, ' ') << child->get_refid() << " "
                  << child->get_name() << " ("
                  << (child->get_parent() ? child->get_parent()->get_refid() :
                                            "")
                  << ")" << std::endl;
        recursive_refid_print(*child, indent + 2);
    }
};

template <typename K, typename V>
static bool
contains(std::unordered_map<K, V> const& map, K const& key) {
    return map.find(key) != map.end();
}

static node::class_reference const&
find(std::vector<node::class_reference> const& list, std::string const& key) {
    for (auto const& child: list) {
        if (child.refid == key) {
            return child;
        }
    }
    throw EXCEPTION("Class reference {} not found", key);
}

static void
compare(
    nlohmann::json const& a,
    nlohmann::json const& b,
    std::string const& path = ".") {
    if (a.is_array()) {
        if (!b.is_array()) {
            throw EXCEPTION("{} expected array but got {}", path, b.dump(2));
        }
        if (a.size() != b.size()) {
            throw EXCEPTION(
                "{} expected array size {} but got {}",
                path,
                a.size(),
                b.size());
        }
        for (size_t i = 0; i < a.size(); i++) {
            compare(a[i], b[i], path + "[" + std::to_string(i) + "].");
        }
    }
    if (a.is_object()) {
        if (!b.is_object()) {
            throw EXCEPTION("{} expected object but got {}", path, b.dump(2));
        }
        if (a.size() != b.size()) {
            throw EXCEPTION(
                "{} expected object size {} but got {}",
                path,
                a.size(),
                b.size());
        }
        for (auto it = a.begin(); it != a.end(); ++it) {
            if (!b.contains(it.key())) {
                throw EXCEPTION(
                    "{} expected object key {} but got {}",
                    path,
                    it.key(),
                    b.size());
            }

            compare(it.value(), b[it.key()], path + it.key() + ".");
        }
    }
    if (a.is_string()) {
        if (!b.is_string()) {
            throw EXCEPTION(
                "{} expected string {} but got {}",
                path,
                a.get<std::string>(),
                b.dump(2));
        }
        if (a.get<std::string>() != b.get<std::string>()) {
            throw EXCEPTION(
                "{} expected string {} but got {}",
                path,
                a.get<std::string>(),
                b.get<std::string>());
        }
    }
    if (a.is_number_integer()) {
        if (!b.is_number_integer()) {
            throw EXCEPTION(
                "{} expected int {} but got {}",
                path,
                a.get<int>(),
                b.dump(2));
        }
        if (a.get<int>() != b.get<int>()) {
            throw EXCEPTION(
                "{} expected int {} but got {}",
                path,
                a.get<int>(),
                b.get<int>());
        }
    }
}

static void
traverse(
    node const& node_,
    std::function<void(node const*, node const*)> const& callback) {
    for (auto const& child: node_.get_children()) {
        callback(&node_, child.get());
        if (child) {
            traverse(*child, callback);
        }
    }
}

static nlohmann::json
jsonFile(std::string const& path) {
    std::ifstream file(path);
    std::string
        str((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
    return nlohmann::json::parse(str);
}

TEST_CASE("Load everything") {
    config c;
    c.copy_images = false;
    doxygen d(c);
    text_plain_printer plainPrinter(c, d);

#ifndef IMPORT_DIR
    return;
#else
    text_markdown_printer markdownPrinter(c, IMPORT_DIR, d);
    json_converter json_c(c, d, plainPrinter, markdownPrinter);
    d.load(IMPORT_DIR);
    d.finalize(plainPrinter, markdownPrinter);

    auto const& index = d.get_index();
    // recursive_refid_print(index);

    SECTION("print child -> parent relation") {
        std::set<std::string> temp;
        traverse(d.get_index(), [&](node const* parent, node const* node) {
            if (temp.find(node->get_refid()) == temp.end()) {
                std::cout << "\"" << node->get_refid() << "\" -> \""
                          << parent->get_refid() << "\"" << std::endl;
                temp.insert(node->get_refid());
            }
        });
    }

    SECTION("Make sure everyone has a parent") {
        traverse(d.get_index(), [](node const* parent, node const* node) {
            INFO(node->get_refid());
            CHECK(node->get_parent() != nullptr);
        });
    }

    SECTION("Make sure everyone does not belong to index except root objects") {
        for (auto const& child: d.get_index().get_children()) {
            traverse(*child, [&](node const* parent, node const* node) {
                if (!is_kind_language(parent->get_kind())) {
                    return;
                }

                INFO(node->get_refid());
                CHECK(node->get_parent() != &d.get_index());
            });
        }
    }

    SECTION("Random lookup via find function") {
#    if defined(__linux__) || defined(__APPLE__)
        CHECK(index.get_refid() == "index");
        CHECK(index.find("group__Engine")->get_refid() == "group__Engine");
        CHECK(index.find("group__Engine")->find_child("group__Audio"));
        CHECK(index.find("group__Engine")->find_child("group__Utils"));
        CHECK(
            index.find("group__Audio")->get_parent()->get_refid()
            == "group__Engine");
        CHECK(
            index.find("group__Utils")->get_parent()->get_refid()
            == "group__Engine");
        CHECK(index.find("group__Utils")->get_kind() == kind::MODULE);
        CHECK(index.find("group__Audio")->get_kind() == kind::MODULE);
        CHECK(index.find("namespaceEngine")->get_refid() == "namespaceEngine");
        CHECK(index.find("namespaceEngine")
                  ->find_child("namespaceEngine_1_1Audio"));
        CHECK(index.find("namespaceEngine")
                  ->find_child("namespaceEngine_1_1Utils"));
        CHECK(
            index.find("namespaceEngine_1_1Audio")->get_parent()->get_refid()
            == "namespaceEngine");
        CHECK(
            index.find("namespaceEngine_1_1Utils")->get_parent()->get_refid()
            == "namespaceEngine");
        CHECK(index.find("namespaceEngine")->get_name() == "Engine");
        CHECK(
            index.find("namespaceEngine_1_1Audio")->get_name()
            == "Engine::Audio");
        CHECK(
            index.find("namespaceEngine_1_1Utils")->get_name()
            == "Engine::Utils");
        CHECK(
            index.find("namespaceEngine_1_1Utils_1_1Path")->get_name()
            == "Engine::Utils::Path");
#    else
        CHECK(index.get_ref_id() == "index");
        CHECK(index.find("group___engine")->get_ref_id() == "group___engine");
        CHECK(index.find("group___engine")->findChild("group___audio"));
        CHECK(index.find("group___engine")->findChild("group___utils"));
        CHECK(
            index.find("group___audio")->get_parent()->get_ref_id()
            == "group___engine");
        CHECK(
            index.find("group___utils")->get_parent()->get_ref_id()
            == "group___engine");
        CHECK(index.find("group___utils")->get_kind() == kind::MODULE);
        CHECK(index.find("group___audio")->get_kind() == kind::MODULE);
        CHECK(
            index.find("namespace_engine")->get_ref_id() == "namespace_engine");
        CHECK(index.find("namespace_engine")
                  ->findChild("namespace_engine_1_1_audio"));
        CHECK(index.find("namespace_engine")
                  ->findChild("namespace_engine_1_1_utils"));
        CHECK(
            index.find("namespace_engine_1_1_audio")->get_parent()->get_ref_id()
            == "namespace_engine");
        CHECK(
            index.find("namespace_engine_1_1_utils")->get_parent()->get_ref_id()
            == "namespace_engine");
        CHECK(index.find("namespace_engine")->getName() == "Engine");
        CHECK(
            index.find("namespace_engine_1_1_audio")->getName()
            == "Engine::Audio");
        CHECK(
            index.find("namespace_engine_1_1_utils")->getName()
            == "Engine::Utils");
        CHECK(
            index.find("namespace_engine_1_1_utils_1_1_path")->getName()
            == "Engine::Utils::Path");
#    endif
    }

    SECTION("Classes with inheritance must have base and derived classes") {
#    if defined(__linux__) || defined(__APPLE__)
        auto const& base = index.find("classEngine_1_1Graphics_1_1Texture2D")
                               ->get_base_classes();
        CHECK(
            find(base, "classEngine_1_1Graphics_1_1Texture").prot
            == visibility::PUBLIC);

        auto const& derived = index.find("classEngine_1_1Graphics_1_1Texture")
                                  ->get_derived_classes();
        CHECK(
            find(derived, "classEngine_1_1Graphics_1_1Texture2D").prot
            == visibility::PUBLIC);
#    else
        auto const& base = index
                               .find("class_engine_1_1_graphics_1_1_texture2_d")
                               ->getBaseClasses();
        CHECK(
            find(base, "class_engine_1_1_graphics_1_1_texture").prot
            == visibility::PUBLIC);

        auto const& derived = index
                                  .find("class_engine_1_1_graphics_1_1_texture")
                                  ->getDerivedClasses();
        CHECK(
            find(derived, "class_engine_1_1_graphics_1_1_texture2_d").prot
            == visibility::PUBLIC);
#    endif
    }
    SECTION("Classes must have valid location data") {
#    if defined(__linux__) || defined(__APPLE__)
        auto const [data, childrenData]
            = index.find("classEngine_1_1Audio_1_1AudioManager")
                  ->load_data(c, plainPrinter, markdownPrinter, d.get_cache());
        auto const& location = data.location;
        CHECK(location.file == "src/Audio/AudioManager.hpp");
        CHECK(location.line == 21);
#    else
        auto const [data, childrenData]
            = index.find("class_engine_1_1_audio_1_1_audio_manager")
                  ->loadData(c, plainPrinter, markdownPrinter, d.getCache());
        auto const& location = data.location;
        CHECK(location.file == "src/Audio/AudioManager.hpp");
        CHECK(location.line == 17);
#    endif
    }
#endif
}
