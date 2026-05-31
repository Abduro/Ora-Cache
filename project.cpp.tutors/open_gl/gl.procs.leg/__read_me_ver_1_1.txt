the query to the Google AI:
is there difference in implementation glViewport in version 1.1 and above in openGL ?

url: https://www.reddit.com/r/GraphicsProgramming/comments/ll7pvw/whats_wrong_with_open_gl_11/ ;

Question:
whats wrong with open GL 1.1?
Everytime I tell someone I'm using open GL1.1 they look at me like ive just commited a warcrime.

shadergremlin
Use whatever you’re comfortable with. The issue with 1.1 is it came out in 1997, so it’s missing a lot of features that we use today, like compute shaders.

xan_da
If you're writing a program, and you want to put some graphics on a window - OpenGL1.1 is very, very easy to work with, compared to its later versions.
It's conceptually simple, and it's a nice, programmer friendly API. So... it gets the job done, and it's easy to use... hm! Sounds great to me!

OpenGL1.1... just lets me do what I need to do, and move on with the rest of my program, without the code getting overly complicated.
But I (like you, with asking this question) have seen no end of apparent putdowns, of why openGL1.1 "shouldn't be used", which all seem to a casual glance to be rather dismissive.

I only lately started to notice how one-sided that analysis is. For example "it doesn't do modern thing X": well, statements like that don't consider the fact that 'modern thing X' is likely completely unnecessary for the task at hand,
and moreover would also introduce a lot of extra learning overhead as well as large amounts of additional program complexity!

I've found that just getting any graphics on a window at all is such a preposterously arduous task, it's absolutely ludicrous to suggest 
that I should need to spend further weeks / months learning (and debugging) GLSL, having to embed shader strings, compile them, assign ids and construct index and command buffers and all that other 2.1+ programmable pipeline complexity...
when all I want to do is put some images, colors, shapes, and maybe some primitive polygons in a window!

I would also point out this: OpenGL1.1 is still 'hardware accelerated graphics'! It's using your GPU.
It's immediately likely more performant than software rendering. And isn't software rendering what most programs you'll encounter these days are actually using!?
Any program written using Javascript's basic Html canvas functions, or for example the shape/image draw functions in CSharp or Java or Python PIL or whatever... none of those are hardware accelerated out of the box. At least, not controllably. 
So most 'by default' behaviour programs aren't performing as well as one would if you're already just using OpenGL1.1.
I don't mean anything by that, other than to make the point that: "So why do all these people using OpenGL 2+ feel the need to put 1.1 down?"

I find it really quite strange (and a bit infuriating) that people only ever seem to talk about OpenGL1.1 being 'outdated/old' implying that it's "slow" and "not-fully-featured".
To the extent that those may be valid to say... that doesn't matter, it's FINE!

Alas for simplicity.
The entire industry is pushing onto Vulkan - a horribly technical, opaque and abstract API which is even more incredibly programmer-unfriendly.
So modern. So fast. Such wow! (No, I'll be sticking to glVertex() for most of my practical code. And when I need shaders, then I'll start introducing shaders).

Zec_kid
That's because 1.1 only has the fixed function pipeline. And without shaders it truly is difficult to do "advanced" rendering techniques. 
In all honesty I've never used it, was well before my time, and I can't really imagine using a framework that only allows for blinn-phong. 
Hell, I work in webGL mostly, and not having a compute shader already feels like all the cool stuff takes so much trickery to achieve. 
Can't imagine losing vertex and fragment shaders too :D

But if you're having fun with it, why not! As long as you don't believe it's state of the art, and sell it as such, I see no harm.
