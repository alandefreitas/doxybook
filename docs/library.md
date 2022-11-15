## Use as a library

You can use this tool as a C++ library. There is a pre-compiled binary executable, static library, and header files on
GitHub release page. Simply link `libdoxybook.a` to your program and provide an include path to the `include` folder.
You can also include the root `CMakeLists.txt` file in this repository and compile it yourself. You will also need to
link `nlohmann/json`, `tinyxml2`, and `fmtlib/fmt`. The API documentation will be added in the future, but here is a
simple example to get your started:

```cpp
#include <nlohmann/json.hpp>
#include <doxybook/doxygen.hpp>
#include <doxybook/exception.hpp>
#include <doxybook/json_converter.hpp>
#include <doxybook/text_markdown_printer.hpp>
#include <doxybook/text_plain_printer.hpp>

int main() {
    using namespace doxybook;

    // Where the XML files are stored
    std::string input_dir = "..";

    // Config file, override any properties you want
    config c;
    c.copy_images = false;

    // The class that will take care of parsing XML files
    doxygen dx(c);

    // There two are used to convert the XML text into markdown (or plain) text.
    // For example: <para><strong>Hello</strong></para> is converted into **Hello**
    text_plain_printer tp(c, dx);
    text_markdown_printer mp(c, input_dir, dx);

    // This is optional and can be used to convert the data in node
    // into nlohmann/json
    json_converter jc(c, dx, tp, mp);

    // Load and parse the XML files, may take few seconds
    dx.load(input_dir);
    dx.finalize(tp, mp);

    // Get the index, this holds hierarchical data.
    // If a class belongs to a namespace, the index will hold the namespace object,
    // but the namespace object will hold the class, not the index.
    const node& index = dx.get_index();

    // Recursive find function via refid_. The refid_ is from the XML files.
    const auto audioBuffer = index.find("class_engine_1_1_audio_1_1_audio_buffer");
    const auto audioBufferConstructor = index.find("classEngine_1_1Audio_1_1AudioBuffer_1ab3f8002fc80d9bff50cfb6095e10a721");
    audioBufferConstructor->get_name(); // Returns "AudioBuffer"

    // Get detailed data of this specific class
    // std::tuple<node::data, node::children_data>
    auto [data, childrenDataMap] = audioBuffer->load_data(c, tp, mp, dx.get_cache());

    // The "data" is type of node::data which contains
    // detailed data for this specific class.
    // The "childrenDataMap" is the same thing, but stored as an unordered map
    // where a key is a pointer to the child (the class' function for example) data.
    auto constructorData& = childrenDataMap.at(audioBufferConstructor);
    
    // ...
}
```
