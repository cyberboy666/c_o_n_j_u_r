#!/usr/bin/env python
# coding: utf-8

# In[4]:

# #+BEGIN_SRC python
#+NAME: 61DC0D98-7222-4B7B-B9A9-9AE4C5EDC9D7
#+BEGIN_SRC ein-python :session http://127.0.0.1:8888/notebooks/foobar.ipynb :results raw drawer

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
    (client.send_message("/shader/0/param", [i, 0.8]))
    time.sleep(.2)
print('okay')
#+END_SRC

#+RESULTS: 61DC0D98-7222-4B7B-B9A9-9AE4C5EDC9D7


#+RESULTS:


# In[7]:


#+NAME: A7671289-EC9B-4E3B-A970-42D3994C7823
#+BEGIN_SRC ein-python :session http://127.0.0.1:8888/notebooks/foobar.ipynb :results raw drawer
# Working:
kscope = 'shaders/invert.frag'
client.send_message("/shader/1/load", [vert_shader, kscope])
client.send_message("/shader/start", True)
client.send_message("/shader/1/is_active", True)
for i in range(4):
    client.send_message("/shader/1/param", [i, 0.5])
    time.sleep(.2)
print("okay")
#+END_SRC

#+RESULTS: A7671289-EC9B-4E3B-A970-42D3994C7823


# In[8]:


# working if you turn off shader0
#+NAME: 628C2C38-949D-46FD-9DC7-AE613D4F4ED4
#+BEGIN_SRC  ein-python :session http://127.0.0.1:8888/notebooks/foobar.ipynb :results raw drawer


client.send_message("/shader/0/is_active", True)
fn = "4k.mp4"
client.send_message("/player/a/load", [fn, 0, 3, 1])
client.send_message("/player/a/play", 0)
#+END_SRC

#+RESULTS: 628C2C38-949D-46FD-9DC7-AE613D4F4ED4
:RESULTS:
:END:
