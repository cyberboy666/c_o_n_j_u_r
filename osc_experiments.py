
from pythonosc import udp_client
import time
localhost = "127.0.0.1"
port = 8000

client = udp_client.SimpleUDPClient(localhost, port)
# working
gen_shader = 'shaders/hypnotic_rings.frag'
vert_shader = 'shaders/default.vert'
client.send_message("/shader/0/load", [vert_shader, gen_shader]) # proj_root + '/kaleidoscope.frag'])
client.send_message("/shader/start", True)
client.send_message("/shader/0/is_active", True)
for i in range(4):
    client.send_message("/shader/0/param", [i, 0.8])
    time.sleep(.2)
    

# Failing:
kscope = 'shaders/kaleidoscope-failing.frag'
client.send_message("/shader/1/load", [vert_shader, kscope]) # proj_root + '/kaleidoscope.frag'])
client.send_message("/shader/start", True)
client.send_message("/shader/1/is_active", True)
for i in range(4):
    client.send_message("/shader/1/param", [i, 0.8])
    time.sleep(.2)

# working but with error:
# [ error ] ofTexture: getTextureData(): texture has not been allocated
fn = "4k.mp4"
client.send_message("/player/a/load", [fn, 0, 3, 1])
client.send_message("/player/a/play", 0)


# I also frequently get this error:
# [verbose] ofShader: setupShaderFromSource(): OpenGL error after checkAndCreateProgram() (probably harmless): error 1282
# Log below
'''
[notice ] the m (mesage) is /shader/0/load ./shaders/default.vert ./shaders/hypnotic_rings.frag
[notice ] loading shader 0 now !!!!
[verbose] ofShader: checkAndCreateProgram(): creating GLSL program
[verbose] ofShader: setupShaderFromSource(): GL_VERTEX_SHADER shader compiled
[verbose] ofShader: setupShaderFromSource(): GL_FRAGMENT_SHADER shader compiled
[verbose] ofShader: linkProgram(): attaching GL_FRAGMENT_SHADER shader to program 28
[verbose] ofShader: linkProgram(): attaching GL_VERTEX_SHADER shader to program 28
[verbose] ofShader: checkProgramLinkStatus(): program 28 linked
[notice ] the m (mesage) is /shader/start T
[notice ] the m (mesage) is /shader/0/is_active T
[notice ] shader0 is active : 1
[notice ] the m (mesage) is /shader/0/param 0 0.8
[notice ] the m (mesage) is /shader/0/param 1 0.8
[notice ] the m (mesage) is /shader/0/param 2 0.8
[notice ] the m (mesage) is /shader/0/param 3 0.8
[notice ] the m (mesage) is /shader/1/load ./shaders/default.vert ./shaders/kaleidoscope-failing.frag
[verbose] ofShader: checkAndCreateProgram(): creating GLSL program
[verbose] ofShader: setupShaderFromSource(): GL_VERTEX_SHADER shader compiled
[verbose] ofShader: setupShaderFromSource(): GL_FRAGMENT_SHADER shader compiled
[verbose] ofShader: linkProgram(): attaching GL_FRAGMENT_SHADER shader to program 31
[verbose] ofShader: linkProgram(): attaching GL_VERTEX_SHADER shader to program 31
[verbose] ofShader: checkProgramLinkStatus(): program 31 linked
[notice ] the m (mesage) is /shader/start T
[notice ] the m (mesage) is /shader/1/is_active T
[notice ] the m (mesage) is /shader/1/param 0 0.8
[notice ] the m (mesage) is /shader/1/param 1 0.8
[notice ] the m (mesage) is /shader/1/param 2 0.8
[notice ] the m (mesage) is /shader/1/param 3 0.8
'''
