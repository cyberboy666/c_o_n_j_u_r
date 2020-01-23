#!/usr/bin/env python
# coding: utf-8

# In[4]:


from pythonosc import udp_client
import time
localhost = "127.0.0.1"
port = 8000

client = udp_client.SimpleUDPClient(localhost, port)
# working
gen_shader = 'shaders/hypnotic_rings.frag'
vert_shader = 'shaders/shader.vert'
client.send_message("/shader/0/load", [vert_shader, gen_shader]) # proj_root + '/kaleidoscope.frag'])
client.send_message("/shader/start", True)
client.send_message("/shader/0/is_active", True)
for i in range(4):
    client.send_message("/shader/0/param", [i, 0.8])
    time.sleep(.2)


# In[7]:


# Working:
zero_input = '/shaders/invert.frag'
client.send_message("/shader/1/load", [vert_shader, kscope])
client.send_message("/shader/start", True)
client.send_message("/shader/1/is_active", True)
for i in range(4):
    client.send_message("/shader/1/param", [i, 0.8])
    time.sleep(.2)


# In[8]:


# working but with warning:
# [ error ] ofTexture: getTextureData(): texture has not been allocated
fn = "4k.mp4"
client.send_message("/player/a/load", [fn, 0, 3, 1])
client.send_message("/player/a/play", 0)
