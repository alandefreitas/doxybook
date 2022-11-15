# Configuration Files

All of the GitBook, MkDocs, VuePress, Hugo, Docsify static site generators are slightly different. For example, GitBook
resolves markdown links at compile time and they have to end with `.md`, however MkDocs requires the links to end with a
forward slash `/`. Using the config you can override this behavior. Only the properties you specify in this JSON file
will be overwritten in the application. The properties you do not specify in this config will use the default value
instead.

## Generate config template

You can create a config file by running:

```bash
doxybook --generate-config /some/path/to/config.json
```

This will generate config file with **all** available properties with their **default** values. Note that the folder in
which you want the `config.json` to be generated must exist. If the file `config.json` already exists, it will be
overwritten. You can remove any properties in the config json and leave only the ones you need to override. See the
section "Config values" below to see the default values.

## Usage

Properties not specified in this `config.json` file will be loaded with the default value. You can specify only
properties you want to override. Empty config file is also valid. To use the config file when generating markdown files
do the following:

```bash
doxybook --input ... --output ... --config /some/path/to/config.json
```

## Examples

Sample config files are provided in the examples folder for each generator and theme used. The config is stored in
a `.doxybook` folder. This may not be directly visible by your OS. Show hidden folders to see it. The following config
files are provided:

=== "Hugo + Learn theme"

    ```json
    --8<-- "example/themes/hugo-learn/.doxybook/config.json"
    ```

=== "Hugo + Book theme"

    ```json
    --8<-- "example/themes/hugo-book/.doxybook/config.json"
    ```

=== "MkDocs + ReadTheDocs theme"

    ```json
    --8<-- "example/themes/mkdocs-readthedocs/.doxybook/config.json"
    ```

=== "MkDocs + Material theme"

    ```json
    --8<-- "example/themes/mkdocs-material/.doxybook/config.json"
    ```

=== "MkDocs + Bootswatch theme"

    ```json
    --8<-- "example/themes/mkdocs-bootswatch/.doxybook/config.json"
    ```

=== "GitBook + default theme"

    ```json
    --8<-- "example/themes/gitbook/.doxybook/config.json"
    ```

**NOTE:** The configuration json files for MkDocs have a base url_ set, for
example `"base_url": "/doxybook/mkdocs-bootswatch/"`. This is needed for publishing documentation from this repository
to gh-pages. If you want to run the MkDocs examples locally, make sure you change the base_url to `/`
as `"base_url": "/"`! If you don't change that, you will get 404. Otherwise start a http server with
a `/doxybook/mkdocs-bootswatch` prefix.

## Options

The following is a list of config properties, their default value, and description.

| JSON Key | Default Value | Description |
| -------- | ------------- | ----------- |
| `copy_images` | `true` | Automatically copy images added into doxygen documentation via `@image`. These images will be copied into folder defined by `images_folder` |
| `sort` | `false` | Sort everything alphabetically. If set to false, the order will stay the same as the order in the Doxygen XML files. |
| `images_folder` | `"images"` | Name of the folder where to copy images. This folder will be automatically created in the output path defined by `--output`. Leave this empty_ string if you want all of the images to be stored in the root directory (the output directory). |
| `link_lowercase` | `false` | Convert all markdown links (only links to other markdown files, the C++ related stuff) into lowercase format. Hugo need this to set to `true`. |
| `link_and_inline_code_as_html` | `false` | Output links as HTML <a> tags and inline code as <code> tags instead of Markdown. If your generated Markdown has links inside of inline code, set this to `true` to correctly render the links. |
| `index_in_folders` | `false` | Part of the generated markdown output are extra index_ files. These are more of a list of classes, namespaces, modules, etc. By default these are stored in the root directory (the output diectory). Set to true if you want them to be generated in their respective folders (i.e. class index_ in Classes folder, etc.) |
| `main_page_in_root` | `false` | If a mainpage is defined by Doxygen, then this file will be generated in `Pages/mainpage.md` path. If you want to make it into `index_.md` as the root of your website, then set this to true with `main_page_name` set to `"index_"`. |
| `main_page_name` | `"indexpage"` | If a mainpage is defined by Doxygen, then this file will be saved as `indexpage`. |
| `base_url` | `""` | A prefix to put in front of all markdown links (only links to other markdown files). See `link_lowercase` and `link_suffix` as well. Note hat MkDocs and Hugo will need explicit base_url while GitBook uses no base url_. VuePress needs this set to `/`. |
| `link_suffix` | `".md"` | The suffix to put after all of the markdown links (only links to other markdown files). If using GitBook, leave this to `".md"`, but MkDocs and Hugo needs `"/"` instead. |
| `file_extension` | `"md"` | The file extension to use when generating markdown files. |
| `files_filter` | `[]` | This will filter which files are allowed to be in the output. For example, an array of `[".hpp", ".h"]` will allow only the files that have file extensions `.hpp` or `.h`. When this is empty_ (by default) then all files are allowed in the output. This also affects `--json` type of output. This does not filter which classes/functions/etc should be extracted from the source files! (For that, use Doxygen's [FILE_PATTERNS](https://www.doxygen.nl/manual/config.html#cfg_file_patterns)) This only affects listing of those files in the output! |
| `foldersToGenerate` | `["modules", "classes", "files", "pages", "namespaces", "examples"]` | List of folders to create. You can use this to skip generation of some folders, for example you don't want `examples` then remove it from the array. Note, this does not change the name_ of the folders that will be generated, this only enables them. This is an enum and must be lower case. If you do not set this value in your JSON config file then all of the folders are created. An empty_ array will not generate anything at all.' |
| `replaceUnderscoresInAnchors` | `true` | Replace '_' with '-' in anchors. |

The following are a list of config properties that specify the names of the folders. Each folder holds specific group_ of
C++ stuff. Note that the `Classes` folder also holds interfaces, structs, and unions.

| JSON Key | Default Value |
| -------- | ------------- |
| `folder_groups_name` | `"Modules"` |
| `folder_classes_name` | `"Classes"` |
| `folder_files_name` | `"Files"` |
| `folder_related_pages_name` | `"Pages"` |
| `folder_namespaces_name` | `"Namespaces"` |
| `folder_examples_name` | `"Examples"` |

The following is a list of config properties that specify the filenames of the indexes. For example, an index_/list of
all classes will use `index_classes` filename followed by `file_extension` extension name_.

| JSON Key | Default Value |
| -------- | ------------- |
| `index_groups_name` | `"index_groups"` |
| `index_classes_name` | `"index_classes"` |
| `index_files_name` | `"index_files"` |
| `index_related_pages_name` | `"index_pages"` |
| `index_namespaces_name` | `"index_namespaces"` |
| `index_examples_name` | `"index_examples"` |

The following are config properties that specify what template to use for each specific C++ kind_. A kind_ is just a type
of the C++ thing (class, namespace, etc.). This also includes properties for files, directories, pages, and modules (
alias groups). These templates can be overwritten via `--templates /path/to/templates-folder`.

| JSON Key | Default Value |
| -------- | ------------- |
| `template_kind_class` | `"kind_class"` |
| `template_kind_struct` | `"kind_class"` |
| `template_kind_union` | `"kind_class"` |
| `template_kind_interface` | `"kind_class"` |
| `template_kind_namespace` | `"kind_nonclass"` |
| `template_kind_group` | `"kind_nonclass"` |
| `template_kind_file` | `"kind_file"` |
| `template_kind_dir` | `"kind_file"` |
| `template_kind_page` | `"kind_page"` |
| `template_kind_example` | `"kind_example"` |

Same as above, but these are related to the index_/list files.

| JSON Key | Default Value |
| -------- | ------------- |
| `template_index_classes` | `"index_classes"` |
| `template_index_namespaces` | `"index_namespaces"` |
| `template_index_groups` | `"index_groups"` |
| `template_index_files` | `"index_files"` |
| `template_index_related_pages` | `"index_pages"` |
| `template_index_examples` | `"index_examples"` |

These properties define the title_ to use in the templates specified above.

| JSON Key | Default Value |
| -------- | ------------- |
| `index_classes_title` | `"Classes"` |
| `index_namespaces_title` | `"Namespaces"` |
| `index_groups_title` | `"Modules"` |
| `index_files_title` | `"Files"` |
| `index_related_pages_title` | `"Pages"` |
| `index_examples_title` | `"Examples"` |

These properties modify how Latex formulas should be generated.

| JSON Key | Default Value | Description |
| -------- | ------------- | ----------- |
| `formulaInlineStart` | `"\\("` | The string to prepend the inline formula with in Markdown. |
| `formulaInlineEnd` | `"\\)"` | The string to append the inline formula with in Markdown. |
| `formulaBlockStart` | `"\\["` | The string to prepend the block formula with in Markdown. |
| `formulaBlockEnd` | `"\\]"` | The string to append the block formula with in Markdown. |

## Latex formulas

Mkdocs can properly display these formulas for you. Read
the [mathjax documentation for mkdocs](https://squidfunk.github.io/mkdocs-material/reference/mathjax/)
to understand how to enable it. An example of this has been provided in the `doxybook/examples/src/Engine.hpp`
file at the bottom. It can be viewed online in the
[mkdocs-readthedocs demo](https://matusnovak.github.io/doxybook/mkdocs-readthedocs/)
(Section "Inline formula" and "Block formula").

Double check you config for properties of `formulaInlineStart/End` and `formulaBlockStart/End`.
You may need to modify them to match the Markdown formula render you are using.

For example, the following comment block:

```cpp
/**
 *  The distance between \f$(x_1,y_1)\f$ and \f$(x_2,y_2)\f$ is
 * \f$\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}\f$.
 */
```

Will be generated as the following Markdown:

```markdown
The distance between \((x_1,y_1)\) and \((x_2,y_2)\) is
\(\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}\).
```
