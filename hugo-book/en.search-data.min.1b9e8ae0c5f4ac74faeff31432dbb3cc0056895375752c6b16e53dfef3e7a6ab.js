"use strict";(function(){const t={cache:!0};t.doc={id:"id",field:["title","content"],store:["title","href","section"]};const e=FlexSearch.create("balance",t);window.bookSearchIndex=e,e.add({id:0,href:"/doxybook/hugo-book/menu/",title:"Menu",section:"Doxybook Example",content:" Classes Namespaces Modules Files Pages Examples "}),e.add({id:1,href:"/doxybook/hugo-book/pages/advanced/",title:"Advanced Usage",section:"Pages",content:` Advanced Usage # This page is for advanced users. Make sure you have first read the introduction.
Updated on 2022-11-17
`}),e.add({id:2,href:"/doxybook/hugo-book/libraries/group__engine/",title:"An example game engine",section:"Libraries",content:` An example game engine Library # This is a brief description to the engine group.
Some detailed description here
Modules # Modules Description Generic assets This is a brief description to the assets group. Audio buffers and devices This is a brief description to the audio group. Graphical related classes This is a brief description to the graphics group. Some gui related stuff and whatever This is a brief description to the gui group. Some useful utilities This is a brief description to the utils group. Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Classes # Classes Description Exception Engine::Exception (class) Functions # Member Functions Description getVersion Returns the version string. (function) Functions # function getVersion # Defined in header \u0026lt;src/Engine.hpp\u0026gt;
std::string getVersion(); Returns the version string.
Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:3,href:"/doxybook/hugo-book/libraries/group__audio/",title:"Audio buffers and devices",section:"Libraries",content:` An example game engine Library: Audio buffers and devices # This is a brief description to the audio group.
Some detailed description here
An example game engine / Audio buffers and devices
Classes # Classes Description AudioBuffer A simple audio buffer to hold PCM samples (class) AudioManager An audio manager that accepts multiple Audio::AudioBuffer instances. (class) Updated on 2022-11-17
`}),e.add({id:4,href:"/doxybook/hugo-book/pages/bug/",title:"Bug List",section:"Pages",content:` Bug List # Class Engine::Audio::AudioBuffer
Some random bug Some other random bug Class Engine::Graphics::Texture
This has some weird bug too! Updated on 2022-11-17
`}),e.add({id:5,href:"/doxybook/hugo-book/classes/",title:"Classes",section:"Doxybook Example",content:` Classes # Class Engine This namespace contains all of the necessary engine components. (namespace) Assets (namespace) Asset (class) Event (union) Loaded (struct) Unloaded (struct) Waiting (struct) Audio (namespace) AudioBuffer A simple audio buffer to hold PCM samples(class) TypedAudioData Use this to populate the buffer. (struct) AudioManager An audio manager that accepts multiple Audio::AudioBuffer instances. (class) Exception (class) Graphics (namespace) Framebuffer (class) Handle (class) Texture This is a base texture class that serves as a base class for other texture types. (interface) Texture2D (class) Texture3D Some deprecated class. (class) Gui (namespace) GuiWidget Some generic gui widget class. (class) Utils (namespace) ArrayView Filesystem path utility functions. (class) Path Filesystem path utility functions. (namespace) Updated on 2022-11-17
`}),e.add({id:6,href:"/doxybook/hugo-book/pages/deprecated/",title:"Deprecated List",section:"Pages",content:` Deprecated List # Member Engine::Audio::AudioBuffer::setCallback (Callback callback)
Use the AudioBuffer::setCallback2 instead Member Engine::Audio::AudioBuffer::setData (const TypedAudioData data[], size_t size)
Use the AudioBuffer::setDataMultiple instead Member Engine::Audio::Callback )(AudioBuffer \u0026amp;buffer, size_t offset)
Use the Audio::Callback2 instead Class Engine::Graphics::Texture3D
Don\u0026rsquo;t use this texture type Updated on 2022-11-17
`}),e.add({id:7,href:"/doxybook/hugo-book/namespaces/namespaceengine/",title:"Engine",section:"Namespaces",content:` Engine # This namespace contains all of the necessary engine components.
An example game engine / Engine
Namespaces # Name Description Engine::Assets Engine::Audio Engine::Graphics Engine::Gui Engine::Utils Classes # Classes Description Exception Engine::Exception (class) Functions # Member Functions Description getVersion Returns the version string. (function) Functions # function getVersion # Defined in header \u0026lt;src/Engine.hpp\u0026gt;
std::string getVersion(); Returns the version string.
Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:8,href:"/doxybook/hugo-book/namespaces/namespaceengine_1_1assets/",title:"Engine::Assets",section:"Namespaces",content:` Engine::Assets # Classes # Classes Description Asset Engine::Assets::Asset (class) Updated on 2022-11-17
`}),e.add({id:9,href:"/doxybook/hugo-book/classes/classengine_1_1assets_1_1asset/",title:"Engine::Assets::Asset",section:"Classes",content:` Engine::Assets::Asset # An example game engine / Generic assets / Asset
Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
class Asset; Public Classes # Name union Event Public Functions # Member Functions Description (constructor) (function) (destructor) = 0 (virtual function) load Call this method to load the asset. (virtual function) unload Call this method to unload the asset. (virtual function) getEvent const Returns the current status of the asset. (function) Public Functions # function Asset # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
explicit Asset(const std::string \u0026amp; name); Exception Safety
Basic exception guarantee.
function ~Asset # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
virtual ~Asset() = 0; Exception Safety
Basic exception guarantee.
function load # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
virtual void load(); Call this method to load the asset.
Exception Safety
Basic exception guarantee.
function unload # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
virtual void unload(); Call this method to unload the asset.
Exception Safety
Basic exception guarantee.
function getEvent # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
const Event \u0026amp; getEvent() const; Returns the current status of the asset.
Description
Use this to determine the state, for example if the assets is being loaded or unloaded.
Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:10,href:"/doxybook/hugo-book/classes/unionengine_1_1assets_1_1asset_1_1event/",title:"Engine::Assets::Asset::Event",section:"Classes",content:` Engine::Assets::Asset::Event # An example game engine / Generic assets / Event
Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
union Event; Public Classes # Name struct Loaded struct Unloaded struct Waiting Public Attributes # Member Public Attributes Description loaded struct Engine::Assets::Asset::Event::Loaded (public variable) unloaded struct Engine::Assets::Asset::Event::Unloaded (public variable) waiting struct Engine::Assets::Asset::Event::Waiting (public variable) Public Attributes # variable loaded # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
struct Engine::Assets::Asset::Event::Loaded loaded; variable unloaded # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
struct Engine::Assets::Asset::Event::Unloaded unloaded; variable waiting # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
struct Engine::Assets::Asset::Event::Waiting waiting; Updated on 2022-11-17
`}),e.add({id:11,href:"/doxybook/hugo-book/classes/structengine_1_1assets_1_1asset_1_1event_1_1loaded/",title:"Engine::Assets::Asset::Event::Loaded",section:"Classes",content:` Engine::Assets::Asset::Event::Loaded # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
struct Loaded; Public Attributes # Member Public Attributes Description success bool (public variable) usage int (public variable) Public Attributes # variable success # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
bool success; variable usage # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
int usage; Updated on 2022-11-17
`}),e.add({id:12,href:"/doxybook/hugo-book/classes/structengine_1_1assets_1_1asset_1_1event_1_1unloaded/",title:"Engine::Assets::Asset::Event::Unloaded",section:"Classes",content:` Engine::Assets::Asset::Event::Unloaded # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
struct Unloaded; Public Attributes # Member Public Attributes Description success bool (public variable) Public Attributes # variable success # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
bool success; Updated on 2022-11-17
`}),e.add({id:13,href:"/doxybook/hugo-book/classes/structengine_1_1assets_1_1asset_1_1event_1_1waiting/",title:"Engine::Assets::Asset::Event::Waiting",section:"Classes",content:` Engine::Assets::Asset::Event::Waiting # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
struct Waiting; Public Attributes # Member Public Attributes Description other The pointer to the other asset this asset is waiting for. (public variable) Public Attributes # variable other # Defined in header \u0026lt;src/Assets/Asset.hpp\u0026gt;
Asset * other; The pointer to the other asset this asset is waiting for.
Note: May be null
Updated on 2022-11-17
`}),e.add({id:14,href:"/doxybook/hugo-book/namespaces/namespaceengine_1_1audio/",title:"Engine::Audio",section:"Namespaces",content:` Engine::Audio # Classes # Classes Description AudioBuffer A simple audio buffer to hold PCM samples (class) AudioManager An audio manager that accepts multiple Audio::AudioBuffer instances. (class) Types # Member Types Definition Callback Some callback function pointer type definition. (typedef) Callback2 Some callback function pointer type definition. (using) Functions # Member Functions Description doSomething Do something with the buffer. (function) Types # typedef Callback # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
typedef int(* Engine::Audio::Callback) (AudioBuffer \u0026amp;buffer, size_t offset); Some callback function pointer type definition.
Parameters:
buffer The buffer this callback is called from offset The offset of the buffer currently playing Deprecated:
Use the Audio::Callback2 instead
using Callback2 # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
using Callback2 = int(*)(AudioBuffer \u0026amp;buffer, size_t offset, void *user); Some callback function pointer type definition.
Parameters:
buffer The buffer this callback is called from offset The offset of the buffer currently playing user User specific data Functions # function doSomething # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
void doSomething(AudioBuffer \u0026amp; buffer); Do something with the buffer.
Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:15,href:"/doxybook/hugo-book/classes/classengine_1_1audio_1_1audiobuffer/",title:"Engine::Audio::AudioBuffer",section:"Classes",content:` Engine::Audio::AudioBuffer # An example game engine / Audio buffers and devices / AudioBuffer
Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
class AudioBuffer; A simple audio buffer to hold PCM samples
Description
Lorem ipsum donor
// Some random code using namespace Engine; Audio::AudioBuffer buffer(\u0026#34;path/to/file.wav\u0026#34;); buffer.play(audioManager); More detailed description!
// Another code sample #include \u0026lt;iostream\u0026gt; using namespace Engine; Audio::AudioBuffer buffer(\u0026#34;path/to/file.wav\u0026#34;); std::cout \u0026lt;\u0026lt; buffer.play(...) \u0026lt;\u0026lt; std::endl; Author: Matus Novak
Date: 2017-2019
Note:
Some random note Some second random note Bug: Some random bug
Some other random bug
Test: Some random test description
Todo: Some random todo
Warning: Some random warning
Precondition: First initialize the system.
Public Classes # Name struct TypedAudioData Use this to populate the buffer. Public Types # Member Types Definition Type Different type of audio formats. (enum) AudioData [Utils::ArrayView](/doxybook/hugo-book/classes/classengine_1_1utils_1_1arrayview/)\u0026lt; T \u0026gt; (using) AudioData8U [AudioData](/doxybook/hugo-book/classes/classengine_1_1audio_1_1audiobuffer/#using-audiodata)\u0026lt; uint8_t \u0026gt; (typedef) Public Functions # Member Functions Description (constructor) Constructor for Audio::AudioBuffer. (function) (destructor) = default Audio::AudioBuffer destructor. (virtual function) play const Play this buffer. (function) stop const Stop this buffer playing. (function) loop const Loop this buffer forever. (function) setData (function) setDataMultiple (function template) setCallback Set the callback function. (function) setCallback2 Set the callback function. (function) Protected Functions # Member Protected Functions Description getData (function) Protected Attributes # Member Protected Attributes Description playing bool (protected variable) Friends # Friends Description AudioManager (public friend class) Audio::doSomething (public friend void) Public Types # enum Type # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
enum class Type; Enumerator Value Description UNKNOWN 0 Dont use this INT_8 1 \u0026laquo; 1 8-bit signed integer INT_16 1 \u0026laquo; 2 16-bit signed integer INT_24 1 \u0026laquo; 3 24-bit signed integer INT_32 1 \u0026laquo; 4 32-bit signed integer FLOAT_32 1 \u0026laquo; 5 32-bit float Different type of audio formats.
using AudioData # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
template \u0026lt;typename T\u0026gt; using AudioData = Utils::ArrayView\u0026lt; T \u0026gt;; typedef AudioData8U # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
typedef AudioData\u0026lt;uint8_t\u0026gt; Engine::Audio::AudioBuffer::AudioData8U; Public Functions # function AudioBuffer # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
explicit AudioBuffer(const std::string \u0026amp; filename); Constructor for Audio::AudioBuffer.
Exception Safety
Basic exception guarantee.
function ~AudioBuffer # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
virtual ~AudioBuffer() = default; Audio::AudioBuffer destructor.
Exception Safety
Basic exception guarantee.
function play # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
void play(AudioManager \u0026amp; manager) const; Play this buffer.
Parameters
manager - Which manager to play the sound with Exception Safety
Basic exception guarantee.
function stop # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
void stop(AudioManager \u0026amp; manager) const; Stop this buffer playing.
Parameters
manager - Which manager to stop the sound with Exception Safety
Basic exception guarantee.
function loop # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
void loop(AudioManager \u0026amp; manager) const; Loop this buffer forever.
Parameters
manager - Which manager to loop the sound with Notes
This will loop forever until you call stop
Exception Safety
Basic exception guarantee.
function setData # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
void setData(const TypedAudioData \u0026amp; data); void setData(const TypedAudioData data[], size_t size); Some deprecated function.
Exception Safety
Basic exception guarantee.
function setDataMultiple # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
template \u0026lt;size_t Size\u0026gt; void setDataMultiple(const TypedAudioData data[Size]); Exception Safety
Basic exception guarantee.
function setCallback # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
void setCallback(Callback callback); Set the callback function.
Parameters
callback - The callback function pointer Exception Safety
Basic exception guarantee.
See Also
Audio::Callback function setCallback2 # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
void setCallback2(Callback2 callback, void * user); Set the callback function.
Parameters
callback - The callback function pointer Exception Safety
Basic exception guarantee.
See Also
Audio::Callback Protected Functions # function getData # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
float * getData(); Exception Safety
Basic exception guarantee.
Protected Attributes # variable playing # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
bool playing {false}; Friends # friend AudioManager # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
friend class AudioManager; friend Audio::doSomething # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
friend void Audio::doSomething(AudioBuffer \u0026amp; buffer); Updated on 2022-11-17
`}),e.add({id:16,href:"/doxybook/hugo-book/classes/structengine_1_1audio_1_1audiobuffer_1_1typedaudiodata/",title:"Engine::Audio::AudioBuffer::TypedAudioData",section:"Classes",content:` Engine::Audio::AudioBuffer::TypedAudioData # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
struct TypedAudioData; Use this to populate the buffer.
Public Attributes # Member Public Attributes Description buffer AudioData8U (public variable) type Type (public variable) Public Attributes # variable buffer # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
AudioData8U buffer; variable type # Defined in header \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt;
Type type; Updated on 2022-11-17
`}),e.add({id:17,href:"/doxybook/hugo-book/classes/classengine_1_1audio_1_1audiomanager/",title:"Engine::Audio::AudioManager",section:"Classes",content:` Engine::Audio::AudioManager # An example game engine / Audio buffers and devices / AudioManager
Defined in header \u0026lt;src/Audio/AudioManager.hpp\u0026gt;
class AudioManager; An audio manager that accepts multiple Audio::AudioBuffer instances.
Description
Lorem Ipsum Donor. Some Random link with bold and italics And the following is a typewritter font. And here is some list items:
First item Second item Third item with bold text Followed by some more text and another list:
First item Second item See Also: Audio::AudioBuffer
Public Functions # Member Functions Description (constructor) (function) (destructor) (function) enque (function) Public Functions # function AudioManager # Defined in header \u0026lt;src/Audio/AudioManager.hpp\u0026gt;
AudioManager(int numOfChannels =128); Exception Safety
Basic exception guarantee.
function ~AudioManager # Defined in header \u0026lt;src/Audio/AudioManager.hpp\u0026gt;
~AudioManager(); Exception Safety
Basic exception guarantee.
function enque # Defined in header \u0026lt;src/Audio/AudioManager.hpp\u0026gt;
void enque(const AudioBuffer \u0026amp; buffer); Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:18,href:"/doxybook/hugo-book/classes/classengine_1_1exception/",title:"Engine::Exception",section:"Classes",content:` Engine::Exception # An example game engine / Exception
Defined in header \u0026lt;src/Exception.hpp\u0026gt;
class Exception; Inherits from exception
Public Functions # Member Functions Description (constructor) (function) what const override (function) Public Functions # function Exception # Defined in header \u0026lt;src/Exception.hpp\u0026gt;
Exception() = default; explicit Exception(std::string msg); Exception Safety
Basic exception guarantee.
function what # Defined in header \u0026lt;src/Exception.hpp\u0026gt;
const char * what() const override; Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:19,href:"/doxybook/hugo-book/namespaces/namespaceengine_1_1graphics/",title:"Engine::Graphics",section:"Namespaces",content:` Engine::Graphics # Classes # Classes Description Framebuffer Engine::Graphics::Framebuffer (class) Handle Engine::Graphics::Handle (class) Texture This is a base texture class that serves as a base class for other texture types. (interface) Texture2D Engine::Graphics::Texture2D (class) Texture3D Some deprecated class. (class) Functions # Member Functions Description getHandle Some namespace inline function. (function) Functions # function getHandle # Defined in header \u0026lt;src/Graphics/Handle.hpp\u0026gt;
int getHandle(Handle \u0026amp; handle); Some namespace inline function.
Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:20,href:"/doxybook/hugo-book/classes/classengine_1_1graphics_1_1framebuffer/",title:"Engine::Graphics::Framebuffer",section:"Classes",content:` Engine::Graphics::Framebuffer # An example game engine / Graphical related classes / Framebuffer
Defined in header \u0026lt;src/Graphics/Framebuffer.hpp\u0026gt;
class Framebuffer; Inherits from Texture, Handle
Public Functions # Member Functions Description (constructor) (function) (destructor) (virtual function) getWidth const override Returns the width of the texture in pixels. (virtual function) getHeight const override Returns the height of the texture in pixels. (virtual function) getDepth const override Returns the depth of the texture in pixels. (virtual function) Additional inherited members # Public Types(inherited from Engine::Graphics::Texture)
Member Types Definition Type Type (enum) Public Functions(inherited from Engine::Graphics::Texture)
Member Functions Description Texture (function) ~Texture = default (virtual function) isLoaded const (function) Protected Attributes(inherited from Engine::Graphics::Texture)
Member Protected Attributes Description loaded bool (protected variable) type Type (protected variable) Public Functions(inherited from Engine::Graphics::Handle)
Member Functions Description Handle = default (function) ~Handle = default (virtual function) getHandle const (function) Protected Attributes(inherited from Engine::Graphics::Handle)
Member Protected Attributes Description handle int (protected variable) Public Functions # function Framebuffer # Defined in header \u0026lt;src/Graphics/Framebuffer.hpp\u0026gt;
Framebuffer(int width, int height); Exception Safety
Basic exception guarantee.
function ~Framebuffer # Defined in header \u0026lt;src/Graphics/Framebuffer.hpp\u0026gt;
virtual ~Framebuffer(); Exception Safety
Basic exception guarantee.
function getWidth # Defined in header \u0026lt;src/Graphics/Framebuffer.hpp\u0026gt;
virtual int getWidth() const override; Returns the width of the texture in pixels.
Return value
Width in pixels
Exception Safety
Basic exception guarantee.
function getHeight # Defined in header \u0026lt;src/Graphics/Framebuffer.hpp\u0026gt;
virtual int getHeight() const override; Returns the height of the texture in pixels.
Return value
Height in pixels
Exception Safety
Basic exception guarantee.
function getDepth # Defined in header \u0026lt;src/Graphics/Framebuffer.hpp\u0026gt;
virtual int getDepth() const override; Returns the depth of the texture in pixels.
Return value
Depth in pixels
Notes
If this texture is 2D the depth is always 1 pixels
Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:21,href:"/doxybook/hugo-book/classes/classengine_1_1graphics_1_1handle/",title:"Engine::Graphics::Handle",section:"Classes",content:` Engine::Graphics::Handle # An example game engine / Graphical related classes / Handle
Defined in header \u0026lt;src/Graphics/Handle.hpp\u0026gt;
class Handle; Inherited by Texture
Public Functions # Member Functions Description (constructor) = default (function) (destructor) = default (virtual function) getHandle const (function) Protected Attributes # Member Protected Attributes Description handle int (protected variable) Public Functions # function Handle # Defined in header \u0026lt;src/Graphics/Handle.hpp\u0026gt;
Handle() = default; Exception Safety
Basic exception guarantee.
function ~Handle # Defined in header \u0026lt;src/Graphics/Handle.hpp\u0026gt;
virtual ~Handle() = default; Exception Safety
Basic exception guarantee.
function getHandle # Defined in header \u0026lt;src/Graphics/Handle.hpp\u0026gt;
int getHandle() const; Exception Safety
Basic exception guarantee.
Protected Attributes # variable handle # Defined in header \u0026lt;src/Graphics/Handle.hpp\u0026gt;
int handle; Updated on 2022-11-17
`}),e.add({id:22,href:"/doxybook/hugo-book/classes/classengine_1_1graphics_1_1texture/",title:"Engine::Graphics::Texture",section:"Classes",content:` Engine::Graphics::Texture # An example game engine / Graphical related classes / Texture
Defined in header \u0026lt;src/Graphics/Texture.hpp\u0026gt;
class Texture; This is a base texture class that serves as a base class for other texture types.
Description
#include \u0026lt;iostream\u0026gt; #include \u0026lt;memory\u0026gt; #include \u0026#34;Engine.hpp\u0026#34; // A dummy example int main() { // Create pixels buffer const auto pixels = std::make_unique\u0026lt;uint8_t[]\u0026gt;(new uint8_t[1024*1024*3]); fillData(*pixels, \u0026#34;path/to/texture.png\u0026#34;); // Create a texture out of the pixels Engine::Graphics::Texture2D texture(1024, 1024, *data); // Done return 0; } Filename: example-1.cpp
Bug: This has some weird bug too!
Inherits from Handle
Inherited by Framebuffer, Texture2D, Texture3D
Public Types # Member Types Definition Type Type (enum) Public Functions # Member Functions Description (constructor) (function) (destructor) = default (virtual function) getWidth const = 0 Returns the width of the texture in pixels. (virtual function) getHeight const = 0 Returns the height of the texture in pixels. (virtual function) getDepth const = 0 Returns the depth of the texture in pixels. (virtual function) isLoaded const (function) Protected Attributes # Member Protected Attributes Description loaded bool (protected variable) type Type (protected variable) Additional inherited members # Public Functions(inherited from Engine::Graphics::Handle)
Member Functions Description Handle = default (function) ~Handle = default (virtual function) getHandle const (function) Protected Attributes(inherited from Engine::Graphics::Handle)
Member Protected Attributes Description handle int (protected variable) Public Types # enum Type # Defined in header \u0026lt;src/Graphics/Texture.hpp\u0026gt;
enum class Type; Enumerator Value Description UNKNOWN 0 RGBA_8 RGB_8 RGBA_16 RGB_16 RGBA_32 RGB_32 Public Functions # function Texture # Defined in header \u0026lt;src/Graphics/Texture.hpp\u0026gt;
explicit Texture(Type type); Exception Safety
Basic exception guarantee.
function ~Texture # Defined in header \u0026lt;src/Graphics/Texture.hpp\u0026gt;
virtual ~Texture() = default; Exception Safety
Basic exception guarantee.
function getWidth # Defined in header \u0026lt;src/Graphics/Texture.hpp\u0026gt;
virtual int getWidth() const = 0; Returns the width of the texture in pixels.
Return value
Width in pixels
Exception Safety
Basic exception guarantee.
function getHeight # Defined in header \u0026lt;src/Graphics/Texture.hpp\u0026gt;
virtual int getHeight() const = 0; Returns the height of the texture in pixels.
Return value
Height in pixels
Exception Safety
Basic exception guarantee.
function getDepth # Defined in header \u0026lt;src/Graphics/Texture.hpp\u0026gt;
virtual int getDepth() const = 0; Returns the depth of the texture in pixels.
Return value
Depth in pixels
Notes
If this texture is 2D the depth is always 1 pixels
Exception Safety
Basic exception guarantee.
function isLoaded # Defined in header \u0026lt;src/Graphics/Texture.hpp\u0026gt;
bool isLoaded() const; Exception Safety
Basic exception guarantee.
Protected Attributes # variable loaded # Defined in header \u0026lt;src/Graphics/Texture.hpp\u0026gt;
bool loaded {false}; variable type # Defined in header \u0026lt;src/Graphics/Texture.hpp\u0026gt;
Type type; Updated on 2022-11-17
`}),e.add({id:23,href:"/doxybook/hugo-book/classes/classengine_1_1graphics_1_1texture2d/",title:"Engine::Graphics::Texture2D",section:"Classes",content:` Engine::Graphics::Texture2D # An example game engine / Graphical related classes / Texture2D
Defined in header \u0026lt;src/Graphics/Texture2D.hpp\u0026gt;
class Texture2D; Inherits from Texture, Handle
Public Functions # Member Functions Description (constructor) (function) (destructor) (virtual function) getWidth const override Returns the width of the texture in pixels. (virtual function) getHeight const override Returns the height of the texture in pixels. (virtual function) getDepth const override Returns the depth of the texture in pixels. (virtual function) Additional inherited members # Public Types(inherited from Engine::Graphics::Texture)
Member Types Definition Type Type (enum) Public Functions(inherited from Engine::Graphics::Texture)
Member Functions Description Texture (function) ~Texture = default (virtual function) isLoaded const (function) Protected Attributes(inherited from Engine::Graphics::Texture)
Member Protected Attributes Description loaded bool (protected variable) type Type (protected variable) Public Functions(inherited from Engine::Graphics::Handle)
Member Functions Description Handle = default (function) ~Handle = default (virtual function) getHandle const (function) Protected Attributes(inherited from Engine::Graphics::Handle)
Member Protected Attributes Description handle int (protected variable) Public Functions # function Texture2D # Defined in header \u0026lt;src/Graphics/Texture2D.hpp\u0026gt;
Texture2D( int width, int height, uint8_t * data, Texture::Type type =Texture::Type::RGBA8); Parameters
data - The pointer to the raw pixels data height - The height of the image held by the data pointer type - What is the type of this pixels array? width - The width of the image held by the data pointer Exception Safety
Basic exception guarantee.
function ~Texture2D # Defined in header \u0026lt;src/Graphics/Texture2D.hpp\u0026gt;
virtual ~Texture2D(); Exception Safety
Basic exception guarantee.
function getWidth # Defined in header \u0026lt;src/Graphics/Texture2D.hpp\u0026gt;
virtual int getWidth() const override; Returns the width of the texture in pixels.
Return value
Width in pixels
Exception Safety
Basic exception guarantee.
function getHeight # Defined in header \u0026lt;src/Graphics/Texture2D.hpp\u0026gt;
virtual int getHeight() const override; Returns the height of the texture in pixels.
Return value
Height in pixels
Exception Safety
Basic exception guarantee.
function getDepth # Defined in header \u0026lt;src/Graphics/Texture2D.hpp\u0026gt;
virtual int getDepth() const override; Returns the depth of the texture in pixels.
Return value
Depth in pixels
Notes
If this texture is 2D the depth is always 1 pixels
Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:24,href:"/doxybook/hugo-book/classes/classengine_1_1graphics_1_1texture3d/",title:"Engine::Graphics::Texture3D",section:"Classes",content:` Engine::Graphics::Texture3D # An example game engine / Graphical related classes / Texture3D
Defined in header \u0026lt;src/Graphics/Texture3D.hpp\u0026gt;
class Texture3D; Some deprecated class.
Deprecated:
Don\u0026rsquo;t use this texture type
Inherits from Texture, Handle
Public Functions # Member Functions Description (constructor) (function) (destructor) (virtual function) getWidth const override Returns the width of the texture in pixels. (virtual function) getHeight const override Returns the height of the texture in pixels. (virtual function) getDepth const override Returns the depth of the texture in pixels. (virtual function) Additional inherited members # Public Types(inherited from Engine::Graphics::Texture)
Member Types Definition Type Type (enum) Public Functions(inherited from Engine::Graphics::Texture)
Member Functions Description Texture (function) ~Texture = default (virtual function) isLoaded const (function) Protected Attributes(inherited from Engine::Graphics::Texture)
Member Protected Attributes Description loaded bool (protected variable) type Type (protected variable) Public Functions(inherited from Engine::Graphics::Handle)
Member Functions Description Handle = default (function) ~Handle = default (virtual function) getHandle const (function) Protected Attributes(inherited from Engine::Graphics::Handle)
Member Protected Attributes Description handle int (protected variable) Public Functions # function Texture3D # Defined in header \u0026lt;src/Graphics/Texture3D.hpp\u0026gt;
Texture3D( int width, int height, int depth, uint8_t * data, Texture::Type type =Texture::Type::RGBA8); Exception Safety
Basic exception guarantee.
function ~Texture3D # Defined in header \u0026lt;src/Graphics/Texture3D.hpp\u0026gt;
virtual ~Texture3D(); Exception Safety
Basic exception guarantee.
function getWidth # Defined in header \u0026lt;src/Graphics/Texture3D.hpp\u0026gt;
virtual int getWidth() const override; Returns the width of the texture in pixels.
Return value
Width in pixels
Exception Safety
Basic exception guarantee.
function getHeight # Defined in header \u0026lt;src/Graphics/Texture3D.hpp\u0026gt;
virtual int getHeight() const override; Returns the height of the texture in pixels.
Return value
Height in pixels
Exception Safety
Basic exception guarantee.
function getDepth # Defined in header \u0026lt;src/Graphics/Texture3D.hpp\u0026gt;
virtual int getDepth() const override; Returns the depth of the texture in pixels.
Return value
Depth in pixels
Notes
If this texture is 2D the depth is always 1 pixels
Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:25,href:"/doxybook/hugo-book/namespaces/namespaceengine_1_1gui/",title:"Engine::Gui",section:"Namespaces",content:` Engine::Gui # Classes # Classes Description GuiWidget Some generic gui widget class. (class) Updated on 2022-11-17
`}),e.add({id:26,href:"/doxybook/hugo-book/classes/classengine_1_1gui_1_1guiwidget/",title:"Engine::Gui::GuiWidget",section:"Classes",content:` Engine::Gui::GuiWidget # An example game engine / Some gui related stuff and whatever / GuiWidget
Defined in header \u0026lt;src/Gui/GuiWidget.hpp\u0026gt;
class GuiWidget; Some generic gui widget class.
Public Slots # Member Slots Description mySlot (slot) Public Signals # Member Signals Description mySignal (signal) Public Functions # Member Functions Description (constructor) (function) (destructor) = default (virtual function) Public Slots # slot mySlot # Defined in header \u0026lt;src/Gui/GuiWidget.hpp\u0026gt;
void mySlot( QObject * object, int a, bool b ); Public Signals # signal mySignal # Defined in header \u0026lt;src/Gui/GuiWidget.hpp\u0026gt;
void mySignal( QObject * object, int a, bool b ); Public Functions # function GuiWidget # Defined in header \u0026lt;src/Gui/GuiWidget.hpp\u0026gt;
explicit GuiWidget(QObject * parent); Exception Safety
Basic exception guarantee.
function ~GuiWidget # Defined in header \u0026lt;src/Gui/GuiWidget.hpp\u0026gt;
virtual ~GuiWidget() = default; Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:27,href:"/doxybook/hugo-book/namespaces/namespaceengine_1_1utils/",title:"Engine::Utils",section:"Namespaces",content:` Engine::Utils # Namespaces # Name Description Engine::Utils::Path Filesystem path utility functions. Classes # Classes Description ArrayView Filesystem path utility functions. (class) Functions # Member Functions Description name_with_underscores (function) Functions # function name_with_underscores # Defined in header \u0026lt;src/Utils/Utils.hpp\u0026gt;
void name_with_underscores(const std::string \u0026amp; arg); Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:28,href:"/doxybook/hugo-book/classes/classengine_1_1utils_1_1arrayview/",title:"Engine::Utils::ArrayView",section:"Classes",content:` Engine::Utils::ArrayView # An example game engine / Some useful utilities / ArrayView
Defined in header \u0026lt;src/Utils/ArrayView.hpp\u0026gt;
template \u0026lt;typename T = uint8_t\u0026gt; class ArrayView; Filesystem path utility functions.
Template Parameters
T - The type of the data, for example uint8_t Public Functions # Member Functions Description (constructor) (function) (destructor) = default (virtual function) data const (virtual function) size const (virtual function) Public Functions # function ArrayView # Defined in header \u0026lt;src/Utils/ArrayView.hpp\u0026gt;
ArrayView(const T * src, size_t len); Exception Safety
Basic exception guarantee.
function ~ArrayView # Defined in header \u0026lt;src/Utils/ArrayView.hpp\u0026gt;
virtual ~ArrayView() = default; Exception Safety
Basic exception guarantee.
function data # Defined in header \u0026lt;src/Utils/ArrayView.hpp\u0026gt;
virtual const T * data() const; Exception Safety
Basic exception guarantee.
function size # Defined in header \u0026lt;src/Utils/ArrayView.hpp\u0026gt;
virtual size_t size() const; Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:29,href:"/doxybook/hugo-book/namespaces/namespaceengine_1_1utils_1_1path/",title:"Engine::Utils::Path",section:"Namespaces",content:` Engine::Utils::Path # Filesystem path utility functions.
An example game engine / Some useful utilities / Path
Functions # Member Functions Description getFilename (function) getExtension (function) Functions # function getFilename # Defined in header \u0026lt;src/Utils/Path.hpp\u0026gt;
std::string getFilename(const std::string \u0026amp; path); Exception Safety
Basic exception guarantee.
function getExtension # Defined in header \u0026lt;src/Utils/Path.hpp\u0026gt;
std::string getExtension(const std::string \u0026amp; path); Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:30,href:"/doxybook/hugo-book/examples/example-1_8cpp-example/",title:"example-1.cpp",section:"Examples",content:` example-1.cpp # This is an example This is detailed docummentation \`\`\`cpp
#include #include #include \u0026ldquo;Engine.hpp\u0026rdquo;
// A dummy example int main() { // Create pixels buffer const auto pixels = std::make_unique\u0026lt;uint8_t[]\u0026gt;(new uint8_t[102410243]); fillData(*pixels, \u0026ldquo;path/to/texture.png\u0026rdquo;);
// Create a texture out of the pixels Engine::Graphics::Texture2D texture(1024, 1024, *data); // Done return 0; }
_Filename: example-1.cpp_ ------------------------------- \u0026lt;sub\u0026gt;Updated on 2022-11-17\u0026lt;/sub\u0026gt; `}),e.add({id:31,href:"/doxybook/hugo-book/examples/",title:"Examples",section:"Doxybook Example",content:` Examples # Example example-1.cpp This is an example. (example) Updated on 2022-11-17
`}),e.add({id:32,href:"/doxybook/hugo-book/files/",title:"Files",section:"Doxybook Example",content:` Files # File src (directory) src/Engine.hpp (file) src/Exception.hpp (file) src/Assets (directory) src/Assets/Asset.hpp (file) src/Assets/Assets.hpp (file) src/Audio (directory) src/Audio/Audio.hpp (file) src/Audio/AudioBuffer.hpp (file) src/Audio/AudioManager.hpp (file) src/Graphics (directory) src/Graphics/Framebuffer.hpp (file) src/Graphics/Graphics.hpp (file) src/Graphics/Handle.hpp (file) src/Graphics/Renderer.hpp (file) src/Graphics/Texture.hpp (file) src/Graphics/Texture2D.hpp (file) src/Graphics/Texture3D.hpp (file) src/Gui (directory) src/Gui/Gui.hpp (file) src/Gui/GuiWidget.hpp (file) src/Utils (directory) src/Utils/ArrayView.hpp (file) src/Utils/Config.hpp (file) src/Utils/Log.hpp (file) src/Utils/Path.hpp (file) src/Utils/Utils.hpp (file) Updated on 2022-11-17
`}),e.add({id:33,href:"/doxybook/hugo-book/libraries/group__assets/",title:"Generic assets",section:"Libraries",content:` An example game engine Library: Generic assets # This is a brief description to the assets group.
Some detailed description here
An example game engine / Generic assets
Classes # Classes Description Event Engine::Assets::Asset::Event (union) Asset Engine::Assets::Asset (class) Updated on 2022-11-17
`}),e.add({id:34,href:"/doxybook/hugo-book/libraries/group__graphics/",title:"Graphical related classes",section:"Libraries",content:` An example game engine Library: Graphical related classes # This is a brief description to the graphics group.
Some detailed description here
An example game engine / Graphical related classes
Classes # Classes Description Framebuffer Engine::Graphics::Framebuffer (class) Handle Engine::Graphics::Handle (class) Texture2D Engine::Graphics::Texture2D (class) Texture3D Some deprecated class. (class) Texture This is a base texture class that serves as a base class for other texture types. (interface) Functions # Member Functions Description getHandle Some namespace inline function. (function) Functions # function getHandle # Defined in header \u0026lt;src/Graphics/Handle.hpp\u0026gt;
int getHandle(Handle \u0026amp; handle); Some namespace inline function.
Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:35,href:"/doxybook/hugo-book/pages/intro/",title:"Introduction",section:"Pages",content:` Introduction # This page introduces the user to the topic. Now you can proceed to the advanced section.
Updated on 2022-11-17
`}),e.add({id:36,href:"/doxybook/hugo-book/libraries/",title:"Libraries",section:"Doxybook Example",content:` Libraries # Library An example game engine This is a brief description to the engine group. (group) Generic assets This is a brief description to the assets group. (group) Audio buffers and devices This is a brief description to the audio group. (group) Graphical related classes This is a brief description to the graphics group. (group) Some gui related stuff and whatever This is a brief description to the gui group. (group) Some useful utilities This is a brief description to the utils group. (group) Updated on 2022-11-17
`}),e.add({id:37,href:"/doxybook/hugo-book/namespaces/",title:"Namespaces",section:"Doxybook Example",content:` Namespaces # Namespace Engine This namespace contains all of the necessary engine components. (namespace) Assets (namespace) Audio (namespace) Graphics (namespace) Gui (namespace) Utils (namespace) Path Filesystem path utility functions. (namespace) Updated on 2022-11-17
`}),e.add({id:38,href:"/doxybook/hugo-book/pages/",title:"Pages",section:"Doxybook Example",content:` Pages # Page Advanced Usage (page) Bug List (page) Deprecated List (page) Doxybook Example (page) Introduction (page) Test List (page) Todo List (page) Updated on 2022-11-17
`}),e.add({id:39,href:"/doxybook/hugo-book/libraries/group__gui/",title:"Some gui related stuff and whatever",section:"Libraries",content:` An example game engine Library: Some gui related stuff and whatever # This is a brief description to the gui group.
Some detailed description here
An example game engine / Some gui related stuff and whatever
Classes # Classes Description GuiWidget Some generic gui widget class. (class) Updated on 2022-11-17
`}),e.add({id:40,href:"/doxybook/hugo-book/libraries/group__utils/",title:"Some useful utilities",section:"Libraries",content:` An example game engine Library: Some useful utilities # This is a brief description to the utils group.
Some detailed description here
An example game engine / Some useful utilities
Namespaces # Name Description Engine::Utils::Path Filesystem path utility functions. Classes # Classes Description ArrayView Filesystem path utility functions. (class) Functions # Member Functions Description name_with_underscores (function) Functions # function name_with_underscores # Defined in header \u0026lt;src/Utils/Utils.hpp\u0026gt;
void name_with_underscores(const std::string \u0026amp; arg); Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:41,href:"/doxybook/hugo-book/files/dir_68267d1309a1af8e8297ef4c3efbcdba/",title:"src",section:"Files",content:` src # Directories # Directories Description src/Assets src/Audio src/Graphics src/Gui src/Utils Files # Files Description src/Engine.hpp src/Exception.hpp Updated on 2022-11-17
`}),e.add({id:42,href:"/doxybook/hugo-book/files/dir_e0c1ede47f21c4a643a1257f949f98e0/",title:"src/Assets",section:"Files",content:` src/Assets # Files # Files Description src/Assets/Asset.hpp src/Assets/Assets.hpp Updated on 2022-11-17
`}),e.add({id:43,href:"/doxybook/hugo-book/files/asset_8hpp/",title:"src/Assets/Asset.hpp",section:"Files",content:` src/Assets/Asset.hpp # #include \u0026lt;src/Assets/Asset.hpp\u0026gt; Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Engine::Assets Classes # Classes Description Asset Engine::Assets::Asset (class) Event Engine::Assets::Asset::Event (union) Loaded Engine::Assets::Asset::Event::Loaded (struct) Unloaded Engine::Assets::Asset::Event::Unloaded (struct) Waiting Engine::Assets::Asset::Event::Waiting (struct) Updated on 2022-11-17
`}),e.add({id:44,href:"/doxybook/hugo-book/files/assets_8hpp/",title:"src/Assets/Assets.hpp",section:"Files",content:` src/Assets/Assets.hpp # #include \u0026lt;src/Assets/Assets.hpp\u0026gt; Updated on 2022-11-17
`}),e.add({id:45,href:"/doxybook/hugo-book/files/dir_c64386e93f356b78d4612c7b7741707c/",title:"src/Audio",section:"Files",content:` src/Audio # Files # Files Description src/Audio/Audio.hpp src/Audio/AudioBuffer.hpp src/Audio/AudioManager.hpp Updated on 2022-11-17
`}),e.add({id:46,href:"/doxybook/hugo-book/files/audio_8hpp/",title:"src/Audio/Audio.hpp",section:"Files",content:` src/Audio/Audio.hpp # #include \u0026lt;src/Audio/Audio.hpp\u0026gt; Updated on 2022-11-17
`}),e.add({id:47,href:"/doxybook/hugo-book/files/audiobuffer_8hpp/",title:"src/Audio/AudioBuffer.hpp",section:"Files",content:` src/Audio/AudioBuffer.hpp # #include \u0026lt;src/Audio/AudioBuffer.hpp\u0026gt; Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Engine::Audio Classes # Classes Description AudioBuffer A simple audio buffer to hold PCM samples (class) TypedAudioData Use this to populate the buffer. (struct) Updated on 2022-11-17
`}),e.add({id:48,href:"/doxybook/hugo-book/files/audiomanager_8hpp/",title:"src/Audio/AudioManager.hpp",section:"Files",content:` src/Audio/AudioManager.hpp # #include \u0026lt;src/Audio/AudioManager.hpp\u0026gt; Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Engine::Audio Classes # Classes Description AudioManager An audio manager that accepts multiple Audio::AudioBuffer instances. (class) Updated on 2022-11-17
`}),e.add({id:49,href:"/doxybook/hugo-book/files/engine_8hpp/",title:"src/Engine.hpp",section:"Files",content:` src/Engine.hpp # #include \u0026lt;src/Engine.hpp\u0026gt; Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Functions # Member Functions Description someGlobalFunc Some global extern function. (function) Functions # function someGlobalFunc # Defined in header \u0026lt;src/Engine.hpp\u0026gt;
std::string someGlobalFunc(); Some global extern function.
Exception Safety
Basic exception guarantee.
Updated on 2022-11-17
`}),e.add({id:50,href:"/doxybook/hugo-book/files/exception_8hpp/",title:"src/Exception.hpp",section:"Files",content:` src/Exception.hpp # #include \u0026lt;src/Exception.hpp\u0026gt; Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Classes # Classes Description Exception Engine::Exception (class) Updated on 2022-11-17
`}),e.add({id:51,href:"/doxybook/hugo-book/files/dir_3419e189e460663ec2c964233bf8dcd6/",title:"src/Graphics",section:"Files",content:` src/Graphics # Files # Files Description src/Graphics/Framebuffer.hpp src/Graphics/Graphics.hpp src/Graphics/Handle.hpp src/Graphics/Renderer.hpp src/Graphics/Texture.hpp src/Graphics/Texture2D.hpp src/Graphics/Texture3D.hpp Updated on 2022-11-17
`}),e.add({id:52,href:"/doxybook/hugo-book/files/framebuffer_8hpp/",title:"src/Graphics/Framebuffer.hpp",section:"Files",content:` src/Graphics/Framebuffer.hpp # #include \u0026lt;src/Graphics/Framebuffer.hpp\u0026gt; Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Engine::Graphics Classes # Classes Description Framebuffer Engine::Graphics::Framebuffer (class) Updated on 2022-11-17
`}),e.add({id:53,href:"/doxybook/hugo-book/files/graphics_8hpp/",title:"src/Graphics/Graphics.hpp",section:"Files",content:` src/Graphics/Graphics.hpp # #include \u0026lt;src/Graphics/Graphics.hpp\u0026gt; Updated on 2022-11-17
`}),e.add({id:54,href:"/doxybook/hugo-book/files/handle_8hpp/",title:"src/Graphics/Handle.hpp",section:"Files",content:` src/Graphics/Handle.hpp # #include \u0026lt;src/Graphics/Handle.hpp\u0026gt; Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Engine::Graphics Classes # Classes Description Handle Engine::Graphics::Handle (class) Updated on 2022-11-17
`}),e.add({id:55,href:"/doxybook/hugo-book/files/renderer_8hpp/",title:"src/Graphics/Renderer.hpp",section:"Files",content:` src/Graphics/Renderer.hpp # #include \u0026lt;src/Graphics/Renderer.hpp\u0026gt; Updated on 2022-11-17
`}),e.add({id:56,href:"/doxybook/hugo-book/files/texture_8hpp/",title:"src/Graphics/Texture.hpp",section:"Files",content:` src/Graphics/Texture.hpp # #include \u0026lt;src/Graphics/Texture.hpp\u0026gt; Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Engine::Graphics Classes # Classes Description Texture This is a base texture class that serves as a base class for other texture types. (interface) Updated on 2022-11-17
`}),e.add({id:57,href:"/doxybook/hugo-book/files/texture2d_8hpp/",title:"src/Graphics/Texture2D.hpp",section:"Files",content:` src/Graphics/Texture2D.hpp # #include \u0026lt;src/Graphics/Texture2D.hpp\u0026gt; Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Engine::Graphics Classes # Classes Description Texture2D Engine::Graphics::Texture2D (class) Updated on 2022-11-17
`}),e.add({id:58,href:"/doxybook/hugo-book/files/texture3d_8hpp/",title:"src/Graphics/Texture3D.hpp",section:"Files",content:` src/Graphics/Texture3D.hpp # #include \u0026lt;src/Graphics/Texture3D.hpp\u0026gt; Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Engine::Graphics Classes # Classes Description Texture3D Some deprecated class. (class) Updated on 2022-11-17
`}),e.add({id:59,href:"/doxybook/hugo-book/files/dir_b5ac5e964c12a6b13a9d28feb9f3d3ed/",title:"src/Gui",section:"Files",content:` src/Gui # Files # Files Description src/Gui/Gui.hpp src/Gui/GuiWidget.hpp Updated on 2022-11-17
`}),e.add({id:60,href:"/doxybook/hugo-book/files/gui_8hpp/",title:"src/Gui/Gui.hpp",section:"Files",content:` src/Gui/Gui.hpp # #include \u0026lt;src/Gui/Gui.hpp\u0026gt; Updated on 2022-11-17
`}),e.add({id:61,href:"/doxybook/hugo-book/files/guiwidget_8hpp/",title:"src/Gui/GuiWidget.hpp",section:"Files",content:` src/Gui/GuiWidget.hpp # #include \u0026lt;src/Gui/GuiWidget.hpp\u0026gt; Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Engine::Gui Classes # Classes Description GuiWidget Some generic gui widget class. (class) Updated on 2022-11-17
`}),e.add({id:62,href:"/doxybook/hugo-book/files/dir_a7363e98f9e0bdd87618633653859815/",title:"src/Utils",section:"Files",content:` src/Utils # Files # Files Description src/Utils/ArrayView.hpp src/Utils/Config.hpp src/Utils/Log.hpp src/Utils/Path.hpp src/Utils/Utils.hpp Updated on 2022-11-17
`}),e.add({id:63,href:"/doxybook/hugo-book/files/arrayview_8hpp/",title:"src/Utils/ArrayView.hpp",section:"Files",content:` src/Utils/ArrayView.hpp # #include \u0026lt;src/Utils/ArrayView.hpp\u0026gt; Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Engine::Utils Classes # Classes Description ArrayView Filesystem path utility functions. (class) Updated on 2022-11-17
`}),e.add({id:64,href:"/doxybook/hugo-book/files/config_8hpp/",title:"src/Utils/Config.hpp",section:"Files",content:` src/Utils/Config.hpp # #include \u0026lt;src/Utils/Config.hpp\u0026gt; Updated on 2022-11-17
`}),e.add({id:65,href:"/doxybook/hugo-book/files/log_8hpp/",title:"src/Utils/Log.hpp",section:"Files",content:` src/Utils/Log.hpp # #include \u0026lt;src/Utils/Log.hpp\u0026gt; Updated on 2022-11-17
`}),e.add({id:66,href:"/doxybook/hugo-book/files/path_8hpp/",title:"src/Utils/Path.hpp",section:"Files",content:` src/Utils/Path.hpp # #include \u0026lt;src/Utils/Path.hpp\u0026gt; Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Engine::Utils Engine::Utils::Path Filesystem path utility functions. Updated on 2022-11-17
`}),e.add({id:67,href:"/doxybook/hugo-book/files/utils_8hpp/",title:"src/Utils/Utils.hpp",section:"Files",content:` src/Utils/Utils.hpp # #include \u0026lt;src/Utils/Utils.hpp\u0026gt; Namespaces # Name Description Engine This namespace contains all of the necessary engine components. Engine::Utils Updated on 2022-11-17
`}),e.add({id:68,href:"/doxybook/hugo-book/pages/test/",title:"Test List",section:"Pages",content:` Test List # Class Engine::Audio::AudioBuffer
Some random test description Updated on 2022-11-17
`}),e.add({id:69,href:"/doxybook/hugo-book/pages/todo/",title:"Todo List",section:"Pages",content:` Todo List # Class Engine::Audio::AudioBuffer
Some random todo Updated on 2022-11-17
`})})()