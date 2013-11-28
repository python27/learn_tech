import simpleguitk as simplegui

def play():
    music.play()

def pause():
    music.pause()

def rewind():
    music.rewind()

def laugh():
    laugh.play()

def vol_down():
    global vol
    if vol > 0:
        vol = vol - 1
    music.set_volume(vol/10.0)
    volume_button.set_text("Volume = " + str(vol))

def vol_up():
    global vol
    if vol < 10:
        vol += 1
    music.set_volume(vol/10.0)
    volume_button.set_text("Volume =" + str(vol))

frame = simplegui.create_frame("Music demo", 250, 250, 100)

frame.add_button("play", play, 100)
frame.add_button("pause", pause, 100)
frame.add_button("rewind", rewind, 100)
frame.add_button("laugh", laugh, 100)
frame.add_button("Vol down", vol_down, 100)
frame.add_button("Vol up", vol_up, 100)

vol = 7
volume_button = frame.add_label("Volume = " + str(vol))

music = simplegui.load_sound("http://commondatastorage.googleapis.com/codeskulpto-assets/Epoq-Lepidoptera.ogg")
laugh = simplegui.load_sound("http://commondatastorage.googleapis.com/codeskulptor-assets/Evilaugh.ogg")

laugh.set_volume(.1)

frame.start()
