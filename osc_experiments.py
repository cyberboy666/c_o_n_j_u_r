from pythonosc import udp_client

# working but with error:
# [ error ] ofTexture: getTextureData(): texture has not been allocated
fn = "/Users/averagehat/of_v0.11.0_osx_release/apps/myApps/c_o_n_j_u_r/4k.mp4"
client.send_message("/player/a/load", [fn, 0, 3, 1])
client.send_message("/player/a/play", 0)

# working
gen_shader = proj_root + '/hypnotic_rings.frag'
vert_shader = proj_root + '/default.vert'
client.send_message("/shader/0/load", [vert_shader, gen_shader]) # proj_root + '/kaleidoscope.frag'])
client.send_message("/shader/start", True)
client.send_message("/shader/0/is_active", True)
for i in range(4):
    client.send_message("/shader/0/param", [i, 0.8])
    time.sleep(.2)
    
# Failing:
kscope = '/kaleidoscope.frag'
client.send_message("/shader/1/load", [proj_root + '/pi.vert', proj_root + '/kaleidoscope.frag']) # proj_root + '/kaleidoscope.frag'])
client.send_message("/shader/start", True)
client.send_message("/shader/1/is_active", True)
for i in range(4):
    client.send_message("/shader/1/param", [i, 0.8])
    time.sleep(.2)
