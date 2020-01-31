#!/usr/bin/env python
# coding: utf-8

#+NAME: 1F53333A-33B1-4FD2-B70D-12742CAE873B
#+BEGIN_SRC ein-python :session http://127.0.0.1:8888/notebooks/foobar.ipynb :results raw drawer
client.send_message("/shader/0/load", [vert_shader, gen_shader]) # proj_root + '/kaleidoscope.frag'])
client.send_message("/shader/start", True)
client.send_message("/shader/0/is_active", True)
for i in range(4):
    (client.send_message("/shader/0/param", [i, 0.8]))
    time.sleep(.2)
#+END_SRC

#+RESULTS: 1F53333A-33B1-4FD2-B70D-12742CAE873B
:RESULTS:
:END:

#+NAME: BB244B41-6DA0-427A-BB8C-99FBC3D7E05F
#+BEGIN_SRC ein-python :session http://127.0.0.1:8888/notebooks/foobar.ipynb :results raw drawer

from pythonosc import udp_client
import time
localhost = "127.0.0.1"
port = 8000

client = udp_client.SimpleUDPClient(localhost, port)
# working
vert_shader = 'shaders/shader.vert'
def msg(id, frag_name, U):
  client.send_message("/shader/start", True)
  msgs = [ ("LOAD_FILE", id, vert_shader, frag_name),
  ("TOGGLE_ACTIVE", id, True)] + \
    [("UPDATE_UNIFORM", id, i, U) for i in range(4)]
  for msg in msgs:
    time.sleep(.1)
    print(msg)
    client.send_message("/graph", msg)


print('okay')
#+END_SRC

#+RESULTS: BB244B41-6DA0-427A-BB8C-99FBC3D7E05F
:RESULTS:
okay
:END:

#+RESULTS: 61DC0D98-7222-4B7B-B9A9-9AE4C5EDC9D7
:RESULTS:
okay
:END:

#+NAME: 0FB62855-FFA2-441B-B7E5-401900072224
#+BEGIN_SRC ein-python :session http://127.0.0.1:8888/notebooks/foobar.ipynb :results raw drawer

#client.send_message("/shader/start", True)
gen_shader = 'shaders/hypnotic_rings.frag'
msg("A1-0", gen_shader, .8)

kscope = 'shaders/kaleidoscope-failing.frag'

# msg("B2-0", kscope, .1)
msg("C3-1", 'shadres/invert.frag' .5)
print('okay')
#+END_SRC

#+RESULTS: 0FB62855-FFA2-441B-B7E5-401900072224
:RESULTS:
('LOAD_FILE', 'A1-0', 'shaders/shader.vert', 'shaders/hypnotic_rings.frag')
('TOGGLE_ACTIVE', 'A1-0', True)

('UPDATE_UNIFORM', 'A1-0', 0, 0.8)
('UPDATE_UNIFORM', 'A1-0', 1, 0.8)

('UPDATE_UNIFORM', 'A1-0', 2, 0.8)
('UPDATE_UNIFORM', 'A1-0', 3, 0.8)

('LOAD_FILE', 'C3-1', 'shaders/shader.vert', 'shaders/invert0.frag')
('TOGGLE_ACTIVE', 'C3-1', True)

('UPDATE_UNIFORM', 'C3-1', 0, 0.5)
('UPDATE_UNIFORM', 'C3-1', 1, 0.5)

('UPDATE_UNIFORM', 'C3-1', 2, 0.5)
('UPDATE_UNIFORM', 'C3-1', 3, 0.5)
okay
:END:

#+NAME: D581ACD9-3CDE-4C1F-AA22-63C50E284A5D
#+BEGIN_SRC ein-python :session http://127.0.0.1:8888/notebooks/foobar.ipynb :results raw drawer
msg("B2-0", 'shaders/invert0.farg', .9)
print('okay')
#+END_SRC

#+RESULTS: D581ACD9-3CDE-4C1F-AA22-63C50E284A5D
:RESULTS:
('LOAD_FILE', 'B2-0', 'shaders/shader.vert', 'shaders/invert0.farg')
('TOGGLE_ACTIVE', 'B2-0', True)

('UPDATE_UNIFORM', 'B2-0', 0, 0.9)
('UPDATE_UNIFORM', 'B2-0', 1, 0.9)

('UPDATE_UNIFORM', 'B2-0', 2, 0.9)
('UPDATE_UNIFORM', 'B2-0', 3, 0.9)
okay
:END:


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
