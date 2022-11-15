# Templates

This doxybook utility uses templates very similar to Jinja on Python. The template engine used
is [inja](https://github.com/pantor/inja) for C++. There are already predefined templates stored inside of the doxybook
executable file. If you do not specify an explicit template folder via `--templates` the default templates will be used.

## Generate default templates

You can dump the default templates into a specific folder by calling doxybook as:

```
doxybook --generate-templates /path/to/folder
```

Note that the folder must exist. If there are any existing files that use the same name_, they will be overwritten.

## Using templates

To use the templates, simply create a folder, put some templates in there **ending with `.tmpl` file extension** and
they will be automatically loaded as:

```
doxybook --input ... --output ... --templates /path/to/folder
```

Just as the config, if the folder does not contain a specific template, the default one will be used. For example,
Hugo (Book theme) needs an extra `type: docs` in the header of the markdown. The
folder `example/hugo-book/.doxybook/templates` contains a single template template file named `meta.tmpl`. This template
is used by `header` template which is then further used by the `kind_class`, `kind_namespace`, and so on. There are no
other template files in that example directory, therefore the default ones will be used.

To use custom templates, simply add them to to the directory specified by the `--templates <dir>`.

**The following are core templates that are needed to generate the output.** All of these templates are defined by the
configuration file (see section "Config values" above). For example, the config key `template_kind_group` is by
default `kind_nonclass`, therefore the render engine expects `kind_nonclass.tmpl` in your templates folder (if exists).

* template_index_examples
* template_index_files
* template_index_groups
* template_index_namespaces
* template_index_related_pages
* template_kind_class
* template_kind_example
* template_kind_file
* template_kind_group
* template_kind_dir
* template_kind_namespace
* template_kind_page
* template_kind_union
* template_kind_interface
* template_kind_struct

**The following are template names used by the core templates above.** These templates are simply dependencies of the
templates above. They are being included by `{{ '{%' }} include "meta" {{ '%}' }}` or by `{{ '{{' }} render(member_details, child) {{ '}}' }}` inside of
the templates above.

* meta
* header
* footer
* index_
* breadcrumbs
* member_details
* mode_details
* class_members_tables
* class_members_inherited_tables
* class_members_details

## Custom templates detailed example

First, generate the default templates (this simply copies them from the executable file to the destination directory) by
running `doxybook --generate-templates <dir>`. Let's say you want to override the fooder with some custom markdown. Find
the `footer.tmpl` file and change the contents with whatever you want. You can delete the rest of the templates that you
have not modified. Now run the executable with the `--templates <dir>` option. This will use your custom `footer.tmpl`.

When the doxybook runs, the list of templates that are loaded is printed to the terminal right at the beginning. For
example, if the template is loaded from your folder, it will
print `Parsing template: 'footer' from file: '/path/to/templates/footer.tmpl`. If the template is loaded from the
executable file itself (the default templates), it will print the following: `Parsing template: 'footer' from default`
instead.

Now, let's say that you want to change how enums are printed (the enum table that has Enumerator, Value, and Description
columns). This is located in the `member_details` template. This template is used
as `{{ '{{' }} render("member_details", child) }}` inside of `class_members_details` and `nonclass_members_details` templates.
So you only need to run `doxybook --generate-templates <dir>` and only keep `member_details.tmpl` and change it however
you want.

Why `render` instead of `include`? The `include` is a keyword from the inja template engine to insert the child template
file. All of the variables that are accessible in the parent_ template are also accessible in the child template being
included. Think of it as copy pasting the contents of the child template and putting them into the parent_ template. The
render method has a different context (global data). This means that you can pass in subset of the data accessible in
the parent_ template. In this case, the `class_members_details` has a JSON data that also has an array `publicTypes` (if
the class/struct has any public types). By default the `class_members_details` has something like this:

```
{{ '{%' }} for child in publicTypes {{ '%}' }}
{{ '{{' }} render("member_details", child) {{ '}}' }}
{{ '{%' }} endfor {{ '%}' }}
```

That will simply loop over the public types and renders the child by passing the array element of `publicTypes` to the
render function. The render function will render the template which global context (all of the accessible data) is going
to be the `child` object.

To see what does the JSON (the global data/context in the template) looks like, simply add `--debug-templates` to the
command line. This will generate `*.md.json` files. Imagine that this JSON is passed into `render(..., json)` when
generating, for example, `group__audio.md` (or any other markdown file except the GitBook summary file).

## Changes to templates since 1.1.0

To include your own custom template, that does not override the default template, use `{{ '{%' }} include "filename.tmpl" {{ '%}' }}`
or `{{ '{{' }} render("filename.tmpl", data) }}` to do so. You need to specify the file extension `.tmpl`. Your custom templates
must end with `.tmpl` file extension.

Including or rendering templates by their name_ with no extension is only possible for the core templates specified in
the config (the properties with name_ that starts with `template...`). This is not recommended but possible.

## Debugging templates

You can add `--debug-templates` into the command line (with no arguments) and a JSON file will be created alongside each
of the markdown file. For example, if a markdown file `group___engine.md` will be created, the JSON will be created
as `group___engine.md.json`.

Why is this useful and why JSON? The JSON is the container between C++ data and
the [inja](https://github.com/pantor/inja) template engine. So inside the template you may find something as
this: `{{ '{%' }} for param in params {{ '%}' }}...{{ '{%' }} endfor {{ '%}' }}`. This `params` variable is extracted from the JSON. This is also the
exact same JSON generated in the JSON-only output. The JSON is simply put into the render function of the inja template
engine.
