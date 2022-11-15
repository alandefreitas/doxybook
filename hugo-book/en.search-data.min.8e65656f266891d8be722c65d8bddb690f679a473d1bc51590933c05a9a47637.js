"use strict";(function(){const t={cache:!0};t.doc={id:"id",field:["title","content"],store:["title","href","section"]};const e=FlexSearch.create("balance",t);window.bookSearchIndex=e,e.add({id:0,href:"/doxybook/hugo-book/menu/",title:"Menu",section:"Doxybook Example",content:" Classes Namespaces Modules Files Pages Examples "}),e.add({id:1,href:"/doxybook/hugo-book/pages/advanced/",title:"Advanced Usage",section:"Pages",content:` Advanced Usage # This page is for advanced users. Make sure you have first read the introduction.
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:2,href:"/doxybook/hugo-book/modules/group__engine/",title:"An example game engine",section:"Modules",content:` An example game engine # This is a brief description to the engine group. More\u0026hellip;
Modules # Name Generic assets This is a brief description to the assets group. Audio buffers and devices This is a brief description to the audio group. Graphical related classes This is a brief description to the graphics group. Some gui related stuff and whatever This is a brief description to the gui group. Some useful utilities This is a brief description to the utils group. Namespaces # Name Engine This namespace contains all of the necessary engine components. Classes # Name class Engine::Exception Functions # Name std::string getVersion()Returns the version string. Detailed Description # This is a brief description to the engine group.
Some detailed description here
Functions Documentation # function getVersion # std::string getVersion() Returns the version string.
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:3,href:"/doxybook/hugo-book/modules/group__audio/",title:"Audio buffers and devices",section:"Modules",content:` Audio buffers and devices # Module: An example game engine
This is a brief description to the audio group. More\u0026hellip;
Classes # Name class Engine::Audio::AudioBuffer A simple audio buffer to hold PCM samples class Engine::Audio::AudioManager An audio manager that accepts multiple Audio::AudioBuffer instances. Detailed Description # This is a brief description to the audio group.
Some detailed description here
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:4,href:"/doxybook/hugo-book/pages/bug/",title:"Bug List",section:"Pages",content:` Bug List # Class Engine::Audio::AudioBuffer
Some random bug Some other random bug Class Engine::Graphics::Texture
This has some weird bug too! Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:5,href:"/doxybook/hugo-book/classes/",title:"Classes",section:"Doxybook Example",content:` Classes # namespace Engine This namespace contains all of the necessary engine components. namespace Assets class Asset union Event struct Loaded struct Unloaded struct Waiting namespace Audio class AudioBuffer A simple audio buffer to hold PCM samples struct TypedAudioData Use this to populate the buffer. class AudioManager An audio manager that accepts multiple Audio::AudioBuffer instances. class Exception namespace Graphics class Framebuffer class Handle interface Texture This is a base texture class that serves as a base class for other texture types. class Texture2D class Texture3D Some deprecated class. namespace Gui class GuiWidget Some generic gui widget class. namespace Utils class ArrayView Filesystem path utility functions. namespace Path Filesystem path utility functions. Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:6,href:"/doxybook/hugo-book/pages/deprecated/",title:"Deprecated List",section:"Pages",content:` Deprecated List # Member Engine::Audio::AudioBuffer::setCallback (Callback callback)
Use the AudioBuffer::setCallback2 instead Member Engine::Audio::AudioBuffer::setData (const TypedAudioData data[], size_t size)
Use the AudioBuffer::setDataMultiple instead Member Engine::Audio::Callback )(AudioBuffer \u0026amp;buffer, size_t offset)
Use the Audio::Callback2 instead Class Engine::Graphics::Texture3D
Don\u0026rsquo;t use this texture type Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:7,href:"/doxybook/hugo-book/namespaces/namespaceengine/",title:"Engine",section:"Namespaces",content:` Engine # Module: An example game engine
This namespace contains all of the necessary engine components. More\u0026hellip;
Namespaces # Name Engine::Assets Engine::Audio Engine::Graphics Engine::Gui Engine::Utils Classes # Name class Engine::Exception Functions # Name std::string getVersion()Returns the version string. Detailed Description # This namespace contains all of the necessary engine components.
See:
Engine::Assets Engine::Audio Engine::Graphics Engine::Utils Functions Documentation # function getVersion # std::string getVersion() Returns the version string.
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:8,href:"/doxybook/hugo-book/namespaces/namespaceengine_1_1assets/",title:"Engine::Assets",section:"Namespaces",content:` Engine::Assets # Classes # Name class Engine::Assets::Asset Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:9,href:"/doxybook/hugo-book/classes/classengine_1_1assets_1_1asset/",title:"Engine::Assets::Asset",section:"Classes",content:` Engine::Assets::Asset # Module: An example game engine / Generic assets
#include \u0026lt;Asset.hpp\u0026gt;
Public Classes # Name union Event Public Functions # Name Asset(const std::string \u0026amp; name) virtual ~Asset() =0 virtual void load()Call this method to load the asset. virtual void unload()Call this method to unload the asset. const Event \u0026amp; getEvent() constReturns the current status of the asset. Public Functions Documentation # function Asset # explicit Asset( const std::string \u0026amp; name ) function ~Asset # virtual ~Asset() =0 function load # virtual void load() Call this method to load the asset.
function unload # virtual void unload() Call this method to unload the asset.
function getEvent # inline const Event \u0026amp; getEvent() const Returns the current status of the asset.
Use this to determine the state, for example if the assets is being loaded or unloaded.
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:10,href:"/doxybook/hugo-book/classes/unionengine_1_1assets_1_1asset_1_1event/",title:"Engine::Assets::Asset::Event",section:"Classes",content:` Engine::Assets::Asset::Event # Module: An example game engine / Generic assets
#include \u0026lt;Asset.hpp\u0026gt;
Public Classes # Name struct Loaded struct Unloaded struct Waiting Public Attributes # Name struct Engine::Assets::Asset::Event::Loaded loaded struct Engine::Assets::Asset::Event::Unloaded unloaded struct Engine::Assets::Asset::Event::Waiting waiting Public Attributes Documentation # variable loaded # struct Engine::Assets::Asset::Event::Loaded loaded; variable unloaded # struct Engine::Assets::Asset::Event::Unloaded unloaded; variable waiting # struct Engine::Assets::Asset::Event::Waiting waiting; Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:11,href:"/doxybook/hugo-book/classes/structengine_1_1assets_1_1asset_1_1event_1_1loaded/",title:"Engine::Assets::Asset::Event::Loaded",section:"Classes",content:` Engine::Assets::Asset::Event::Loaded # #include \u0026lt;Asset.hpp\u0026gt;
Public Attributes # Name bool success int usage Public Attributes Documentation # variable success # bool success; variable usage # int usage; Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:12,href:"/doxybook/hugo-book/classes/structengine_1_1assets_1_1asset_1_1event_1_1unloaded/",title:"Engine::Assets::Asset::Event::Unloaded",section:"Classes",content:` Engine::Assets::Asset::Event::Unloaded # #include \u0026lt;Asset.hpp\u0026gt;
Public Attributes # Name bool success Public Attributes Documentation # variable success # bool success; Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:13,href:"/doxybook/hugo-book/classes/structengine_1_1assets_1_1asset_1_1event_1_1waiting/",title:"Engine::Assets::Asset::Event::Waiting",section:"Classes",content:` Engine::Assets::Asset::Event::Waiting # #include \u0026lt;Asset.hpp\u0026gt;
Public Attributes # Name Asset * other The pointer to the other asset this asset is waiting for. Public Attributes Documentation # variable other # Asset * other; The pointer to the other asset this asset is waiting for.
Note: May be null
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:14,href:"/doxybook/hugo-book/namespaces/namespaceengine_1_1audio/",title:"Engine::Audio",section:"Namespaces",content:` Engine::Audio # Classes # Name class Engine::Audio::AudioBuffer A simple audio buffer to hold PCM samples class Engine::Audio::AudioManager An audio manager that accepts multiple Audio::AudioBuffer instances. Types # Name typedef int(*)(AudioBuffer \u0026amp;buffer, size_t offset) Callback Some callback function pointer type definition. using int(*)(AudioBuffer \u0026amp;buffer, size_t offset, void *user) Callback2 Some callback function pointer type definition. Functions # Name void doSomething(AudioBuffer \u0026amp; buffer)Do something with the buffer. Types Documentation # typedef Callback # typedef int(* Engine::Audio::Callback) (AudioBuffer \u0026amp;buffer, size_t offset); Some callback function pointer type definition.
Parameters:
buffer The buffer this callback is called from offset The offset of the buffer currently playing Deprecated:
Use the Audio::Callback2 instead
using Callback2 # using Engine::Audio::Callback2 = typedef int (*)(AudioBuffer\u0026amp; buffer, size_t offset, void* user); Some callback function pointer type definition.
Parameters:
buffer The buffer this callback is called from offset The offset of the buffer currently playing user User specific data Functions Documentation # function doSomething # void doSomething( AudioBuffer \u0026amp; buffer ) Do something with the buffer.
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:15,href:"/doxybook/hugo-book/classes/classengine_1_1audio_1_1audiobuffer/",title:"Engine::Audio::AudioBuffer",section:"Classes",content:` Engine::Audio::AudioBuffer # Module: An example game engine / Audio buffers and devices
A simple audio buffer to hold PCM samples More\u0026hellip;
#include \u0026lt;AudioBuffer.hpp\u0026gt;
Public Classes # Name struct TypedAudioData Use this to populate the buffer. Public Types # Name enum class Type { UNKNOWN = 0, INT_8 = 1 \u0026laquo; 1, INT_16 = 1 \u0026laquo; 2, INT_24 = 1 \u0026laquo; 3, INT_32 = 1 \u0026laquo; 4, FLOAT_32 = 1 \u0026laquo; 5}Different type of audio formats. template \u0026lt;typename T \u0026gt; using Utils::ArrayView\u0026lt; T \u0026gt; AudioData typedef AudioData\u0026lt; uint8_t \u0026gt; AudioData8U Public Functions # Name AudioBuffer(const std::string \u0026amp; filename)Constructor for Audio::AudioBuffer. virtual ~AudioBuffer() =defaultAudio::AudioBuffer destructor. void play(AudioManager \u0026amp; manager) constPlay this buffer. void stop(AudioManager \u0026amp; manager) constStop this buffer playing. void loop(AudioManager \u0026amp; manager) constLoop this buffer forever. void setData(const TypedAudioData \u0026amp; data) template \u0026lt;size_t Size\u0026gt; void setDataMultiple(const TypedAudioData data[Size]) void setData(const TypedAudioData data[], size_t size)Some deprecated function. void setCallback(Callback callback)Set the callback function. void setCallback2(Callback2 callback, void * user)Set the callback function. Protected Functions # Name float * getData() Protected Attributes # Name bool playing Friends # Name class AudioManager void Audio::doSomething(AudioBuffer \u0026amp; buffer) Detailed Description # class Engine::Audio::AudioBuffer; A simple audio buffer to hold PCM samples
Author: Matus Novak
Date: 2017-2019
Note:
Some random note Some second random note Bug: Some random bug
Some other random bug
Test: Some random test description
Todo: Some random todo
Warning: Some random warning
Precondition: First initialize the system.
Lorem ipsum donor
// Some random code using namespace Engine; Audio::AudioBuffer buffer(\u0026#34;path/to/file.wav\u0026#34;); buffer.play(audioManager); More detailed description!
// Another code sample #include \u0026lt;iostream\u0026gt; using namespace Engine; Audio::AudioBuffer buffer(\u0026#34;path/to/file.wav\u0026#34;); std::cout \u0026lt;\u0026lt; buffer.play(...) \u0026lt;\u0026lt; std::endl; Public Types Documentation # enum Type # Enumerator Value Description UNKNOWN 0 Dont use this INT_8 1 \u0026laquo; 1 8-bit signed integer INT_16 1 \u0026laquo; 2 16-bit signed integer INT_24 1 \u0026laquo; 3 24-bit signed integer INT_32 1 \u0026laquo; 4 32-bit signed integer FLOAT_32 1 \u0026laquo; 5 32-bit float Different type of audio formats.
using AudioData # template \u0026lt;typename T \u0026gt; using Engine::Audio::AudioBuffer::AudioData = Utils::ArrayView\u0026lt;T\u0026gt;; typedef AudioData8U # typedef AudioData\u0026lt;uint8_t\u0026gt; Engine::Audio::AudioBuffer::AudioData8U; Public Functions Documentation # function AudioBuffer # explicit AudioBuffer( const std::string \u0026amp; filename ) Constructor for Audio::AudioBuffer.
function ~AudioBuffer # virtual ~AudioBuffer() =default Audio::AudioBuffer destructor.
function play # void play( AudioManager \u0026amp; manager ) const Play this buffer.
Parameters:
manager Which manager to play the sound with Exceptions:
Exception If this buffer is already playing function stop # void stop( AudioManager \u0026amp; manager ) const Stop this buffer playing.
Parameters:
manager Which manager to stop the sound with Exceptions:
Exception If this buffer is already stopped function loop # void loop( AudioManager \u0026amp; manager ) const Loop this buffer forever.
Parameters:
manager Which manager to loop the sound with Exceptions:
Exception If this buffer is already looping Note: This will loop forever until you call stop
function setData # void setData( const TypedAudioData \u0026amp; data ) function setDataMultiple # template \u0026lt;size_t Size\u0026gt; inline void setDataMultiple( const TypedAudioData data[Size] ) function setData # void setData( const TypedAudioData data[], size_t size ) Some deprecated function.
Deprecated:
Use the AudioBuffer::setDataMultiple instead
function setCallback # void setCallback( Callback callback ) Set the callback function.
Parameters:
callback The callback function pointer Deprecated:
Use the AudioBuffer::setCallback2 instead
See: Audio::Callback
function setCallback2 # void setCallback2( Callback2 callback, void * user ) Set the callback function.
Parameters:
callback The callback function pointer See: Audio::Callback
Protected Functions Documentation # function getData # float * getData() Protected Attributes Documentation # variable playing # bool playing {false}; Friends # friend AudioManager # friend class AudioManager; friend Audio::doSomething # friend void Audio::doSomething( AudioBuffer \u0026amp; buffer ); Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:16,href:"/doxybook/hugo-book/classes/structengine_1_1audio_1_1audiobuffer_1_1typedaudiodata/",title:"Engine::Audio::AudioBuffer::TypedAudioData",section:"Classes",content:` Engine::Audio::AudioBuffer::TypedAudioData # Use this to populate the buffer.
#include \u0026lt;AudioBuffer.hpp\u0026gt;
Public Attributes # Name AudioData8U buffer Type type Public Attributes Documentation # variable buffer # AudioData8U buffer; variable type # Type type; Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:17,href:"/doxybook/hugo-book/classes/classengine_1_1audio_1_1audiomanager/",title:"Engine::Audio::AudioManager",section:"Classes",content:` Engine::Audio::AudioManager # Module: An example game engine / Audio buffers and devices
An audio manager that accepts multiple Audio::AudioBuffer instances. More\u0026hellip;
#include \u0026lt;AudioManager.hpp\u0026gt;
Public Functions # Name AudioManager(int numOfChannels =128) ~AudioManager() void enque(const AudioBuffer \u0026amp; buffer) Detailed Description # class Engine::Audio::AudioManager; An audio manager that accepts multiple Audio::AudioBuffer instances.
See: Audio::AudioBuffer
Lorem Ipsum Donor. Some Random link with bold and italics And the following is a typewritter font. And here is some list items:
First item Second item Third item with bold text Followed by some more text and another list:
First item Second item Public Functions Documentation # function AudioManager # AudioManager( int numOfChannels =128 ) function ~AudioManager # ~AudioManager() function enque # void enque( const AudioBuffer \u0026amp; buffer ) Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:18,href:"/doxybook/hugo-book/classes/classengine_1_1exception/",title:"Engine::Exception",section:"Classes",content:` Engine::Exception # Module: An example game engine
#include \u0026lt;Exception.hpp\u0026gt;
Inherits from exception
Public Functions # Name Exception() =default Exception(std::string msg) const char * what() const override Public Functions Documentation # function Exception # Exception() =default function Exception # inline explicit Exception( std::string msg ) function what # inline const char * what() const override Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:19,href:"/doxybook/hugo-book/namespaces/namespaceengine_1_1graphics/",title:"Engine::Graphics",section:"Namespaces",content:` Engine::Graphics # Classes # Name class Engine::Graphics::Framebuffer class Engine::Graphics::Handle interface Engine::Graphics::Texture This is a base texture class that serves as a base class for other texture types. class Engine::Graphics::Texture2D class Engine::Graphics::Texture3D Some deprecated class. Functions # Name int getHandle(Handle \u0026amp; handle)Some namespace inline function. Functions Documentation # function getHandle # inline int getHandle( Handle \u0026amp; handle ) Some namespace inline function.
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:20,href:"/doxybook/hugo-book/classes/classengine_1_1graphics_1_1framebuffer/",title:"Engine::Graphics::Framebuffer",section:"Classes",content:` Engine::Graphics::Framebuffer # Module: An example game engine / Graphical related classes
#include \u0026lt;Framebuffer.hpp\u0026gt;
Inherits from Engine::Graphics::Texture, Engine::Graphics::Handle
Public Functions # Name Framebuffer(int width, int height) virtual ~Framebuffer() virtual int getWidth() const overrideReturns the width of the texture in pixels. virtual int getHeight() const overrideReturns the height of the texture in pixels. virtual int getDepth() const overrideReturns the depth of the texture in pixels. Additional inherited members # Public Types inherited from Engine::Graphics::Texture
Name enum class Type { UNKNOWN, RGBA_8, RGB_8, RGBA_16, RGB_16, RGBA_32, RGB_32} Public Functions inherited from Engine::Graphics::Texture
Name Texture(Type type) virtual ~Texture() =default bool isLoaded() const Protected Attributes inherited from Engine::Graphics::Texture
Name bool loaded Type type Public Functions inherited from Engine::Graphics::Handle
Name Handle() =default virtual ~Handle() =default int getHandle() const Protected Attributes inherited from Engine::Graphics::Handle
Name int handle Public Functions Documentation # function Framebuffer # Framebuffer( int width, int height ) function ~Framebuffer # virtual ~Framebuffer() function getWidth # virtual int getWidth() const override Returns the width of the texture in pixels.
Return: Width in pixels
Reimplements: Engine::Graphics::Texture::getWidth
function getHeight # virtual int getHeight() const override Returns the height of the texture in pixels.
Return: Height in pixels
Reimplements: Engine::Graphics::Texture::getHeight
function getDepth # virtual int getDepth() const override Returns the depth of the texture in pixels.
Return: Depth in pixels
Note: If this texture is 2D the depth is always 1 pixels
Reimplements: Engine::Graphics::Texture::getDepth
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:21,href:"/doxybook/hugo-book/classes/classengine_1_1graphics_1_1handle/",title:"Engine::Graphics::Handle",section:"Classes",content:` Engine::Graphics::Handle # Module: An example game engine / Graphical related classes
#include \u0026lt;Handle.hpp\u0026gt;
Inherited by Engine::Graphics::Texture
Public Functions # Name Handle() =default virtual ~Handle() =default int getHandle() const Protected Attributes # Name int handle Public Functions Documentation # function Handle # Handle() =default function ~Handle # virtual ~Handle() =default function getHandle # inline int getHandle() const Protected Attributes Documentation # variable handle # int handle; Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:22,href:"/doxybook/hugo-book/classes/classengine_1_1graphics_1_1texture/",title:"Engine::Graphics::Texture",section:"Classes",content:` Engine::Graphics::Texture # Module: An example game engine / Graphical related classes
This is a base texture class that serves as a base class for other texture types. More\u0026hellip;
#include \u0026lt;Texture.hpp\u0026gt;
Inherits from Engine::Graphics::Handle
Inherited by Engine::Graphics::Framebuffer, Engine::Graphics::Texture2D, Engine::Graphics::Texture3D
Public Types # Name enum class Type { UNKNOWN = 0, RGBA_8, RGB_8, RGBA_16, RGB_16, RGBA_32, RGB_32} Public Functions # Name Texture(Type type) virtual ~Texture() =default virtual int getWidth() const =0Returns the width of the texture in pixels. virtual int getHeight() const =0Returns the height of the texture in pixels. virtual int getDepth() const =0Returns the depth of the texture in pixels. bool isLoaded() const Protected Attributes # Name bool loaded Type type Additional inherited members # Public Functions inherited from Engine::Graphics::Handle
Name Handle() =default virtual ~Handle() =default int getHandle() const Protected Attributes inherited from Engine::Graphics::Handle
Name int handle Detailed Description # class Engine::Graphics::Texture; This is a base texture class that serves as a base class for other texture types.
Bug: This has some weird bug too!
#include \u0026lt;iostream\u0026gt; #include \u0026lt;memory\u0026gt; #include \u0026#34;Engine.hpp\u0026#34; // A dummy example int main() { // Create pixels buffer const auto pixels = std::make_unique\u0026lt;uint8_t[]\u0026gt;(new uint8_t[1024*1024*3]); fillData(*pixels, \u0026#34;path/to/texture.png\u0026#34;); // Create a texture out of the pixels Engine::Graphics::Texture2D texture(1024, 1024, *data); // Done return 0; } Filename: example-1.cpp
Public Types Documentation # enum Type # Enumerator Value Description UNKNOWN 0 RGBA_8 RGB_8 RGBA_16 RGB_16 RGBA_32 RGB_32 Public Functions Documentation # function Texture # explicit Texture( Type type ) function ~Texture # virtual ~Texture() =default function getWidth # virtual int getWidth() const =0 Returns the width of the texture in pixels.
Return: Width in pixels
Reimplemented by: Engine::Graphics::Framebuffer::getWidth, Engine::Graphics::Texture3D::getWidth, Engine::Graphics::Texture2D::getWidth
function getHeight # virtual int getHeight() const =0 Returns the height of the texture in pixels.
Return: Height in pixels
Reimplemented by: Engine::Graphics::Framebuffer::getHeight, Engine::Graphics::Texture3D::getHeight, Engine::Graphics::Texture2D::getHeight
function getDepth # virtual int getDepth() const =0 Returns the depth of the texture in pixels.
Return: Depth in pixels
Note: If this texture is 2D the depth is always 1 pixels
Reimplemented by: Engine::Graphics::Framebuffer::getDepth, Engine::Graphics::Texture3D::getDepth, Engine::Graphics::Texture2D::getDepth
function isLoaded # inline bool isLoaded() const Does some more things
Protected Attributes Documentation # variable loaded # bool loaded {false}; variable type # Type type; Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:23,href:"/doxybook/hugo-book/classes/classengine_1_1graphics_1_1texture2d/",title:"Engine::Graphics::Texture2D",section:"Classes",content:` Engine::Graphics::Texture2D # Module: An example game engine / Graphical related classes
#include \u0026lt;Texture2D.hpp\u0026gt;
Inherits from Engine::Graphics::Texture, Engine::Graphics::Handle
Public Functions # Name Texture2D(int width, int height, uint8_t * data, Texture::Type type =Texture::Type::RGBA8) virtual ~Texture2D() virtual int getWidth() const overrideReturns the width of the texture in pixels. virtual int getHeight() const overrideReturns the height of the texture in pixels. virtual int getDepth() const overrideReturns the depth of the texture in pixels. Additional inherited members # Public Types inherited from Engine::Graphics::Texture
Name enum class Type { UNKNOWN, RGBA_8, RGB_8, RGBA_16, RGB_16, RGBA_32, RGB_32} Public Functions inherited from Engine::Graphics::Texture
Name Texture(Type type) virtual ~Texture() =default bool isLoaded() const Protected Attributes inherited from Engine::Graphics::Texture
Name bool loaded Type type Public Functions inherited from Engine::Graphics::Handle
Name Handle() =default virtual ~Handle() =default int getHandle() const Protected Attributes inherited from Engine::Graphics::Handle
Name int handle Public Functions Documentation # function Texture2D # Texture2D( int width, int height, uint8_t * data, Texture::Type type =Texture::Type::RGBA8 ) Parameters:
data The pointer to the raw pixels data width The width of the image held by the data pointer height The height of the image held by the data pointer type What is the type of this pixels array? function ~Texture2D # virtual ~Texture2D() function getWidth # virtual int getWidth() const override Returns the width of the texture in pixels.
Return: Width in pixels
Reimplements: Engine::Graphics::Texture::getWidth
function getHeight # virtual int getHeight() const override Returns the height of the texture in pixels.
Return: Height in pixels
Reimplements: Engine::Graphics::Texture::getHeight
function getDepth # virtual int getDepth() const override Returns the depth of the texture in pixels.
Return: Depth in pixels
Note: If this texture is 2D the depth is always 1 pixels
Reimplements: Engine::Graphics::Texture::getDepth
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:24,href:"/doxybook/hugo-book/classes/classengine_1_1graphics_1_1texture3d/",title:"Engine::Graphics::Texture3D",section:"Classes",content:` Engine::Graphics::Texture3D # Module: An example game engine / Graphical related classes
Some deprecated class. More\u0026hellip;
#include \u0026lt;Texture3D.hpp\u0026gt;
Inherits from Engine::Graphics::Texture, Engine::Graphics::Handle
Public Functions # Name Texture3D(int width, int height, int depth, uint8_t * data, Texture::Type type =Texture::Type::RGBA8) virtual ~Texture3D() virtual int getWidth() const overrideReturns the width of the texture in pixels. virtual int getHeight() const overrideReturns the height of the texture in pixels. virtual int getDepth() const overrideReturns the depth of the texture in pixels. Additional inherited members # Public Types inherited from Engine::Graphics::Texture
Name enum class Type { UNKNOWN, RGBA_8, RGB_8, RGBA_16, RGB_16, RGBA_32, RGB_32} Public Functions inherited from Engine::Graphics::Texture
Name Texture(Type type) virtual ~Texture() =default bool isLoaded() const Protected Attributes inherited from Engine::Graphics::Texture
Name bool loaded Type type Public Functions inherited from Engine::Graphics::Handle
Name Handle() =default virtual ~Handle() =default int getHandle() const Protected Attributes inherited from Engine::Graphics::Handle
Name int handle Detailed Description # class Engine::Graphics::Texture3D; Some deprecated class.
Deprecated:
Don\u0026rsquo;t use this texture type
Public Functions Documentation # function Texture3D # Texture3D( int width, int height, int depth, uint8_t * data, Texture::Type type =Texture::Type::RGBA8 ) function ~Texture3D # virtual ~Texture3D() function getWidth # virtual int getWidth() const override Returns the width of the texture in pixels.
Return: Width in pixels
Reimplements: Engine::Graphics::Texture::getWidth
function getHeight # virtual int getHeight() const override Returns the height of the texture in pixels.
Return: Height in pixels
Reimplements: Engine::Graphics::Texture::getHeight
function getDepth # virtual int getDepth() const override Returns the depth of the texture in pixels.
Return: Depth in pixels
Note: If this texture is 2D the depth is always 1 pixels
Reimplements: Engine::Graphics::Texture::getDepth
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:25,href:"/doxybook/hugo-book/namespaces/namespaceengine_1_1gui/",title:"Engine::Gui",section:"Namespaces",content:` Engine::Gui # Classes # Name class Engine::Gui::GuiWidget Some generic gui widget class. Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:26,href:"/doxybook/hugo-book/classes/classengine_1_1gui_1_1guiwidget/",title:"Engine::Gui::GuiWidget",section:"Classes",content:` Engine::Gui::GuiWidget # Module: An example game engine / Some gui related stuff and whatever
Some generic gui widget class.
#include \u0026lt;GuiWidget.hpp\u0026gt;
Public Slots # Name void mySlot(QObject * object, int a, bool b) Public Signals # Name void mySignal(QObject * object, int a, bool b) Public Functions # Name GuiWidget(QObject * parent) virtual ~GuiWidget() =default Public Slots Documentation # slot mySlot # void mySlot( QObject * object, int a, bool b ) Public Signals Documentation # signal mySignal # void mySignal( QObject * object, int a, bool b ) Public Functions Documentation # function GuiWidget # explicit GuiWidget( QObject * parent ) function ~GuiWidget # virtual ~GuiWidget() =default Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:27,href:"/doxybook/hugo-book/namespaces/namespaceengine_1_1utils/",title:"Engine::Utils",section:"Namespaces",content:` Engine::Utils # Namespaces # Name Engine::Utils::Path Filesystem path utility functions. Classes # Name class Engine::Utils::ArrayView Filesystem path utility functions. Functions # Name void name_with_underscores(const std::string \u0026amp; arg) Functions Documentation # function name_with_underscores # inline void name_with_underscores( const std::string \u0026amp; arg ) Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:28,href:"/doxybook/hugo-book/classes/classengine_1_1utils_1_1arrayview/",title:"Engine::Utils::ArrayView",section:"Classes",content:` Engine::Utils::ArrayView # Module: An example game engine / Some useful utilities
Filesystem path utility functions. More\u0026hellip;
#include \u0026lt;ArrayView.hpp\u0026gt;
Public Functions # Name ArrayView(const T * src, size_t len) virtual ~ArrayView() =default virtual const T * data() const virtual size_t size() const Detailed Description # template \u0026lt;typename T =uint8_t\u0026gt; class Engine::Utils::ArrayView; Filesystem path utility functions.
Template Parameters:
T The type of the data, for example uint8_t Public Functions Documentation # function ArrayView # ArrayView( const T * src, size_t len ) function ~ArrayView # virtual ~ArrayView() =default function data # virtual const T * data() const function size # virtual size_t size() const Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:29,href:"/doxybook/hugo-book/namespaces/namespaceengine_1_1utils_1_1path/",title:"Engine::Utils::Path",section:"Namespaces",content:` Engine::Utils::Path # Module: An example game engine / Some useful utilities
Filesystem path utility functions.
Functions # Name std::string getFilename(const std::string \u0026amp; path) std::string getExtension(const std::string \u0026amp; path) Functions Documentation # function getFilename # std::string getFilename( const std::string \u0026amp; path ) function getExtension # std::string getExtension( const std::string \u0026amp; path ) Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:30,href:"/doxybook/hugo-book/examples/example-1_8cpp-example/",title:"example-1.cpp",section:"Examples",content:` example-1.cpp # This is an example This is detailed docummentation \`\`\`cpp
#include #include #include \u0026ldquo;Engine.hpp\u0026rdquo;
// A dummy example int main() { // Create pixels buffer const auto pixels = std::make_unique\u0026lt;uint8_t[]\u0026gt;(new uint8_t[102410243]); fillData(*pixels, \u0026ldquo;path/to/texture.png\u0026rdquo;);
// Create a texture out of the pixels Engine::Graphics::Texture2D texture(1024, 1024, *data); // Done return 0; }
_Filename: example-1.cpp_ ------------------------------- Updated on 2022-11-15 at 04:08:15 +0000 `}),e.add({id:31,href:"/doxybook/hugo-book/examples/",title:"Examples",section:"Doxybook Example",content:` Examples # example example-1.cpp This is an example. Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:32,href:"/doxybook/hugo-book/files/",title:"Files",section:"Doxybook Example",content:` Files # dir src file Engine.hpp file Exception.hpp dir Assets file Asset.hpp file Assets.hpp dir Audio file Audio.hpp file AudioBuffer.hpp file AudioManager.hpp dir Graphics file Framebuffer.hpp file Graphics.hpp file Handle.hpp file Renderer.hpp file Texture.hpp file Texture2D.hpp file Texture3D.hpp dir Gui file Gui.hpp file GuiWidget.hpp dir Utils file ArrayView.hpp file Config.hpp file Log.hpp file Path.hpp file Utils.hpp Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:33,href:"/doxybook/hugo-book/modules/group__assets/",title:"Generic assets",section:"Modules",content:` Generic assets # Module: An example game engine
This is a brief description to the assets group. More\u0026hellip;
Classes # Name union Engine::Assets::Asset::Event class Engine::Assets::Asset Detailed Description # This is a brief description to the assets group.
Some detailed description here
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:34,href:"/doxybook/hugo-book/modules/group__graphics/",title:"Graphical related classes",section:"Modules",content:` Graphical related classes # Module: An example game engine
This is a brief description to the graphics group. More\u0026hellip;
Classes # Name class Engine::Graphics::Framebuffer class Engine::Graphics::Handle class Engine::Graphics::Texture2D class Engine::Graphics::Texture3D Some deprecated class. interface Engine::Graphics::Texture This is a base texture class that serves as a base class for other texture types. Functions # Name int getHandle(Handle \u0026amp; handle)Some namespace inline function. Detailed Description # This is a brief description to the graphics group.
Some detailed description here
Functions Documentation # function getHandle # inline int getHandle( Handle \u0026amp; handle ) Some namespace inline function.
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:35,href:"/doxybook/hugo-book/pages/intro/",title:"Introduction",section:"Pages",content:` Introduction # This page introduces the user to the topic. Now you can proceed to the advanced section.
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:36,href:"/doxybook/hugo-book/modules/",title:"Modules",section:"Doxybook Example",content:` Modules # group An example game engine This is a brief description to the engine group. group Generic assets This is a brief description to the assets group. group Audio buffers and devices This is a brief description to the audio group. group Graphical related classes This is a brief description to the graphics group. group Some gui related stuff and whatever This is a brief description to the gui group. group Some useful utilities This is a brief description to the utils group. Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:37,href:"/doxybook/hugo-book/namespaces/",title:"Namespaces",section:"Doxybook Example",content:` Namespaces # namespace Engine This namespace contains all of the necessary engine components. namespace Assets namespace Audio namespace Graphics namespace Gui namespace Utils namespace Path Filesystem path utility functions. Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:38,href:"/doxybook/hugo-book/pages/",title:"Pages",section:"Doxybook Example",content:` Pages # page Advanced Usage page Bug List page Deprecated List page Doxybook Example page Introduction page Test List page Todo List Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:39,href:"/doxybook/hugo-book/modules/group__gui/",title:"Some gui related stuff and whatever",section:"Modules",content:` Some gui related stuff and whatever # Module: An example game engine
This is a brief description to the gui group. More\u0026hellip;
Classes # Name class Engine::Gui::GuiWidget Some generic gui widget class. Detailed Description # This is a brief description to the gui group.
Some detailed description here
Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:40,href:"/doxybook/hugo-book/modules/group__utils/",title:"Some useful utilities",section:"Modules",content:` Some useful utilities # Module: An example game engine
This is a brief description to the utils group. More\u0026hellip;
Namespaces # Name Engine::Utils::Path Filesystem path utility functions. Classes # Name class Engine::Utils::ArrayView Filesystem path utility functions. Functions # Name void name_with_underscores(const std::string \u0026amp; arg) Defines # Name ENGINE_VERSION Autogenerated version string by CMake. LOG_DEBUG(MSG, \u0026hellip;) Detailed Description # This is a brief description to the utils group.
Some detailed description here
Functions Documentation # function name_with_underscores # inline void name_with_underscores( const std::string \u0026amp; arg ) Macros Documentation # define ENGINE_VERSION # #define ENGINE_VERSION \u0026#34;v1.0.1\u0026#34; Autogenerated version string by CMake.
define LOG_DEBUG # #define LOG_DEBUG( MSG, ... ) printf(MSG, ##__VA_ARGS__) Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:41,href:"/doxybook/hugo-book/files/dir_68267d1309a1af8e8297ef4c3efbcdba/",title:"src",section:"Files",content:` src # Directories # Name src/Assets src/Audio src/Graphics src/Gui src/Utils Files # Name src/Engine.hpp src/Exception.hpp Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:42,href:"/doxybook/hugo-book/files/dir_e0c1ede47f21c4a643a1257f949f98e0/",title:"src/Assets",section:"Files",content:` src/Assets # Files # Name src/Assets/Asset.hpp src/Assets/Assets.hpp Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:43,href:"/doxybook/hugo-book/files/asset_8hpp/",title:"src/Assets/Asset.hpp",section:"Files",content:` src/Assets/Asset.hpp # Namespaces # Name Engine This namespace contains all of the necessary engine components. Engine::Assets Classes # Name class Engine::Assets::Asset union Engine::Assets::Asset::Event struct Engine::Assets::Asset::Event::Loaded struct Engine::Assets::Asset::Event::Unloaded struct Engine::Assets::Asset::Event::Waiting Source code # #pragma once #include \u0026lt;queue\u0026gt; #include \u0026lt;string\u0026gt; namespace Engine { namespace Assets { class Asset { public: union Event { struct Loaded { bool success; int usage; } loaded; struct Unloaded { bool success; } unloaded; struct Waiting { Asset* other; } waiting; }; explicit Asset(const std::string\u0026amp; name); virtual ~Asset() = 0; virtual void load(); virtual void unload(); const Event\u0026amp; getEvent() const { return event; } private: Event event; }; } } Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:44,href:"/doxybook/hugo-book/files/assets_8hpp/",title:"src/Assets/Assets.hpp",section:"Files",content:` src/Assets/Assets.hpp # Source code # #pragma once #include \u0026#34;AssetModel.hpp\u0026#34; #include \u0026#34;AssetManager.hpp\u0026#34; Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:45,href:"/doxybook/hugo-book/files/dir_c64386e93f356b78d4612c7b7741707c/",title:"src/Audio",section:"Files",content:` src/Audio # Files # Name src/Audio/Audio.hpp src/Audio/AudioBuffer.hpp src/Audio/AudioManager.hpp Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:46,href:"/doxybook/hugo-book/files/audio_8hpp/",title:"src/Audio/Audio.hpp",section:"Files",content:` src/Audio/Audio.hpp # Source code # #pragma once #include \u0026#34;AudioBuffer.hpp\u0026#34; #include \u0026#34;AudioManager.hpp\u0026#34; Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:47,href:"/doxybook/hugo-book/files/audiobuffer_8hpp/",title:"src/Audio/AudioBuffer.hpp",section:"Files",content:` src/Audio/AudioBuffer.hpp # Namespaces # Name Engine This namespace contains all of the necessary engine components. Engine::Audio Classes # Name class Engine::Audio::AudioBuffer A simple audio buffer to hold PCM samples struct Engine::Audio::AudioBuffer::TypedAudioData Use this to populate the buffer. Source code # #pragma once #include \u0026#34;../Utils/ArrayView.hpp\u0026#34; namespace Engine { namespace Audio { class AudioManager; class AudioBuffer; typedef int (*Callback)(AudioBuffer\u0026amp; buffer, size_t offset); using Callback2 = int (*)(AudioBuffer\u0026amp; buffer, size_t offset, void* user); extern void doSomething(AudioBuffer\u0026amp; buffer); class AudioBuffer { public: enum class Type { UNKNOWN = 0, INT_8 = 1 \u0026lt;\u0026lt; 1, INT_16 = 1 \u0026lt;\u0026lt; 2, INT_24 = 1 \u0026lt;\u0026lt; 3, INT_32 = 1 \u0026lt;\u0026lt; 4, FLOAT_32 = 1 \u0026lt;\u0026lt; 5 }; template \u0026lt;typename T\u0026gt; using AudioData = Utils::ArrayView\u0026lt;T\u0026gt;; typedef AudioData\u0026lt;uint8_t\u0026gt; AudioData8U; struct TypedAudioData { AudioData8U buffer; Type type; }; explicit AudioBuffer(const std::string\u0026amp; filename); virtual ~AudioBuffer() = default; void play(AudioManager\u0026amp; manager) const; void stop(AudioManager\u0026amp; manager) const; void loop(AudioManager\u0026amp; manager) const; void setData(const TypedAudioData\u0026amp; data); template \u0026lt;size_t Size\u0026gt; void setDataMultiple(const TypedAudioData data[Size]) { } void setData(const TypedAudioData data[], size_t size); friend class AudioManager; friend void Audio::doSomething(AudioBuffer\u0026amp; buffer); void setCallback(Callback callback); void setCallback2(Callback2 callback, void* user); protected: float* getData(); bool playing{false}; }; } // namespace Audio } // namespace Engine Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:48,href:"/doxybook/hugo-book/files/audiomanager_8hpp/",title:"src/Audio/AudioManager.hpp",section:"Files",content:` src/Audio/AudioManager.hpp # Namespaces # Name Engine This namespace contains all of the necessary engine components. Engine::Audio Classes # Name class Engine::Audio::AudioManager An audio manager that accepts multiple Audio::AudioBuffer instances. Source code # #pragma once #include \u0026#34;AudioBuffer.hpp\u0026#34; namespace Engine { namespace Audio { class AudioManager final { public: AudioManager(int numOfChannels = 128); ~AudioManager(); void enque(const AudioBuffer\u0026amp; buffer); }; } // namespace Audio } // namespace Engine Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:49,href:"/doxybook/hugo-book/files/engine_8hpp/",title:"src/Engine.hpp",section:"Files",content:` src/Engine.hpp # Namespaces # Name Engine This namespace contains all of the necessary engine components. Functions # Name std::string someGlobalFunc()Some global extern function. Functions Documentation # function someGlobalFunc # std::string someGlobalFunc() Some global extern function.
Source code # #include \u0026#34;Assets/Assets.hpp\u0026#34; #include \u0026#34;Audio/Audio.hpp\u0026#34; #include \u0026#34;Exception.hpp\u0026#34; #include \u0026#34;Graphics/Graphics.hpp\u0026#34; #include \u0026#34;Gui/Gui.hpp\u0026#34; #include \u0026#34;Utils/Utils.hpp\u0026#34; extern std::string someGlobalFunc(); namespace Engine { extern std::string getVersion(); } // namespace Engine //----------------------------------------------------------- //----------------------------------------------------------- Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:50,href:"/doxybook/hugo-book/files/exception_8hpp/",title:"src/Exception.hpp",section:"Files",content:` src/Exception.hpp # Namespaces # Name Engine This namespace contains all of the necessary engine components. Classes # Name class Engine::Exception Source code # #pragma once #include \u0026lt;exception\u0026gt; #include \u0026lt;string\u0026gt; namespace Engine { class Exception: public std::exception { public: Exception() = default; explicit Exception(std::string msg) : msg(std::move(msg)) { } const char* what() const throw() override { return msg.c_str(); } private: std::string msg; }; } Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:51,href:"/doxybook/hugo-book/files/dir_3419e189e460663ec2c964233bf8dcd6/",title:"src/Graphics",section:"Files",content:` src/Graphics # Files # Name src/Graphics/Framebuffer.hpp src/Graphics/Graphics.hpp src/Graphics/Handle.hpp src/Graphics/Renderer.hpp src/Graphics/Texture.hpp src/Graphics/Texture2D.hpp src/Graphics/Texture3D.hpp Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:52,href:"/doxybook/hugo-book/files/framebuffer_8hpp/",title:"src/Graphics/Framebuffer.hpp",section:"Files",content:` src/Graphics/Framebuffer.hpp # Namespaces # Name Engine This namespace contains all of the necessary engine components. Engine::Graphics Classes # Name class Engine::Graphics::Framebuffer Source code # #pragma once #include \u0026#34;Texture.hpp\u0026#34; namespace Engine { namespace Graphics { class Framebuffer : public Texture { public: Framebuffer(int width, int height); virtual ~Framebuffer(); int getWidth() const override; int getHeight() const override; int getDepth() const override; }; } // namespace Graphics } // namespace Engine Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:53,href:"/doxybook/hugo-book/files/graphics_8hpp/",title:"src/Graphics/Graphics.hpp",section:"Files",content:` src/Graphics/Graphics.hpp # Source code # #pragma once #include \u0026#34;Framebuffer.hpp\u0026#34; #include \u0026#34;Handle.hpp\u0026#34; #include \u0026#34;Renderer.hpp\u0026#34; #include \u0026#34;Texture.hpp\u0026#34; #include \u0026#34;Texture2D.hpp\u0026#34; #include \u0026#34;Texture3D.hpp\u0026#34; Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:54,href:"/doxybook/hugo-book/files/handle_8hpp/",title:"src/Graphics/Handle.hpp",section:"Files",content:` src/Graphics/Handle.hpp # Namespaces # Name Engine This namespace contains all of the necessary engine components. Engine::Graphics Classes # Name class Engine::Graphics::Handle Source code # #pragma once namespace Engine { namespace Graphics { class Handle { public: Handle() = default; virtual ~Handle() = default; int getHandle() const { return handle; } protected: // OpenGL handle int handle; }; inline int getHandle(Handle\u0026amp; handle) { return handle.getHandle(); } } // namespace Graphics } // namespace Engine Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:55,href:"/doxybook/hugo-book/files/renderer_8hpp/",title:"src/Graphics/Renderer.hpp",section:"Files",content:` src/Graphics/Renderer.hpp # Source code # #pragma once Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:56,href:"/doxybook/hugo-book/files/texture_8hpp/",title:"src/Graphics/Texture.hpp",section:"Files",content:` src/Graphics/Texture.hpp # Namespaces # Name Engine This namespace contains all of the necessary engine components. Engine::Graphics Classes # Name interface Engine::Graphics::Texture This is a base texture class that serves as a base class for other texture types. Source code # #pragma once #include \u0026#34;Handle.hpp\u0026#34; namespace Engine { namespace Graphics { class Texture : protected Handle { public: enum class Type { UNKNOWN = 0, RGBA_8, RGB_8, RGBA_16, RGB_16, RGBA_32, RGB_32 }; explicit Texture(Type type); virtual ~Texture() = default; virtual int getWidth() const = 0; virtual int getHeight() const = 0; virtual int getDepth() const = 0; inline bool isLoaded() const { return loaded; } protected: bool loaded{false}; Type type; }; } // namespace Graphics } // namespace Engine Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:57,href:"/doxybook/hugo-book/files/texture2d_8hpp/",title:"src/Graphics/Texture2D.hpp",section:"Files",content:` src/Graphics/Texture2D.hpp # Namespaces # Name Engine This namespace contains all of the necessary engine components. Engine::Graphics Classes # Name class Engine::Graphics::Texture2D Source code # #pragma once #include \u0026#34;Texture.hpp\u0026#34; namespace Engine { namespace Graphics { class Texture2D : public Texture { public: Texture2D(int width, int height, uint8_t* data, Texture::Type type = Texture::Type::RGBA8); virtual ~Texture2D(); int getWidth() const override; int getHeight() const override; int getDepth() const override; }; } // namespace Graphics } // namespace Engine Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:58,href:"/doxybook/hugo-book/files/texture3d_8hpp/",title:"src/Graphics/Texture3D.hpp",section:"Files",content:` src/Graphics/Texture3D.hpp # Namespaces # Name Engine This namespace contains all of the necessary engine components. Engine::Graphics Classes # Name class Engine::Graphics::Texture3D Some deprecated class. Source code # #pragma once #pragma once #include \u0026#34;Texture.hpp\u0026#34; namespace Engine { namespace Graphics { class Texture3D : public Texture { public: Texture3D(int width, int height, int depth, uint8_t* data, Texture::Type type = Texture::Type::RGBA8); virtual ~Texture3D(); int getWidth() const override; int getHeight() const override; int getDepth() const override; }; } // namespace Graphics } // namespace Engine Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:59,href:"/doxybook/hugo-book/files/dir_b5ac5e964c12a6b13a9d28feb9f3d3ed/",title:"src/Gui",section:"Files",content:` src/Gui # Files # Name src/Gui/Gui.hpp src/Gui/GuiWidget.hpp Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:60,href:"/doxybook/hugo-book/files/gui_8hpp/",title:"src/Gui/Gui.hpp",section:"Files",content:` src/Gui/Gui.hpp # Source code # #pragma once Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:61,href:"/doxybook/hugo-book/files/guiwidget_8hpp/",title:"src/Gui/GuiWidget.hpp",section:"Files",content:` src/Gui/GuiWidget.hpp # Namespaces # Name Engine This namespace contains all of the necessary engine components. Engine::Gui Classes # Name class Engine::Gui::GuiWidget Some generic gui widget class. Source code # #pragma once class QObject; // Forward definition namespace Engine { namespace Gui { class GuiWidget { public: explicit GuiWidget(QObject* parent); virtual ~GuiWidget() = default; signals: void mySignal(QObject* object, int a, bool b); public slots: void mySlot(QObject* object, int a, bool b); private: QObject* parent; }; } // namespace Gui } // namespace Engine Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:62,href:"/doxybook/hugo-book/files/dir_a7363e98f9e0bdd87618633653859815/",title:"src/Utils",section:"Files",content:` src/Utils # Files # Name src/Utils/ArrayView.hpp src/Utils/Config.hpp src/Utils/Log.hpp src/Utils/Path.hpp src/Utils/Utils.hpp Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:63,href:"/doxybook/hugo-book/files/arrayview_8hpp/",title:"src/Utils/ArrayView.hpp",section:"Files",content:` src/Utils/ArrayView.hpp # Namespaces # Name Engine This namespace contains all of the necessary engine components. Engine::Utils Classes # Name class Engine::Utils::ArrayView Filesystem path utility functions. Source code # #pragma once namespace Engine { namespace Utils { template\u0026lt;typename T = uint8_t\u0026gt; class ArrayView { public: ArrayView(const T* src, size_t len); virtual ~ArrayView() = default; virtual const T* data() const; virtual size_t size() const; }; } } Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:64,href:"/doxybook/hugo-book/files/config_8hpp/",title:"src/Utils/Config.hpp",section:"Files",content:` src/Utils/Config.hpp # Defines # Name ENGINE_VERSION Autogenerated version string by CMake. ENGINE_ARCH Macros Documentation # define ENGINE_VERSION # #define ENGINE_VERSION \u0026#34;v1.0.1\u0026#34; Autogenerated version string by CMake.
define ENGINE_ARCH # #define ENGINE_ARCH \u0026#34;amd64\u0026#34; Source code # #pragma once #define ENGINE_VERSION \u0026#34;v1.0.1\u0026#34; #define ENGINE_ARCH \u0026#34;amd64\u0026#34; Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:65,href:"/doxybook/hugo-book/files/log_8hpp/",title:"src/Utils/Log.hpp",section:"Files",content:` src/Utils/Log.hpp # Defines # Name LOG_DEBUG(MSG, \u0026hellip;) Macros Documentation # define LOG_DEBUG # #define LOG_DEBUG( MSG, ... ) printf(MSG, ##__VA_ARGS__) Source code # #pragma once #include \u0026lt;stdio.h\u0026gt; #define LOG_DEBUG(MSG, ...) printf(MSG, ##__VA_ARGS__) Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:66,href:"/doxybook/hugo-book/files/path_8hpp/",title:"src/Utils/Path.hpp",section:"Files",content:` src/Utils/Path.hpp # Namespaces # Name Engine This namespace contains all of the necessary engine components. Engine::Utils Engine::Utils::Path Filesystem path utility functions. Source code # #pragma once #include \u0026lt;string\u0026gt; namespace Engine { namespace Utils { namespace Path { std::string getFilename(const std::string\u0026amp; path); std::string getExtension(const std::string\u0026amp; path); } } } Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:67,href:"/doxybook/hugo-book/files/utils_8hpp/",title:"src/Utils/Utils.hpp",section:"Files",content:` src/Utils/Utils.hpp # Namespaces # Name Engine This namespace contains all of the necessary engine components. Engine::Utils Source code # #pragma once #include \u0026#34;Path.hpp\u0026#34; #include \u0026#34;ArrayView.hpp\u0026#34; #include \u0026#34;Config.hpp\u0026#34; #include \u0026#34;Log.hpp\u0026#34; namespace Engine { namespace Utils { inline void name_with_underscores(const std::string\u0026amp; arg) { (void)arg; } } } Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:68,href:"/doxybook/hugo-book/pages/test/",title:"Test List",section:"Pages",content:` Test List # Class Engine::Audio::AudioBuffer
Some random test description Updated on 2022-11-15 at 04:08:15 +0000
`}),e.add({id:69,href:"/doxybook/hugo-book/pages/todo/",title:"Todo List",section:"Pages",content:` Todo List # Class Engine::Audio::AudioBuffer
Some random todo Updated on 2022-11-15 at 04:08:15 +0000
`})})()