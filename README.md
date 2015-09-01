# 3D AmbiLight

Ambilight for 3D hologram, reads pixels from 3 videos (each from a different perspective) and sends them to LED light strips.

### Dependencies

Software

* openFrameworks (tested using git version with Visual Studio 2015)
* ofxGui (comes with oF)
* ofxNetwork (comes with oF)
* [ofxArtnet](https://github.com/hiroyuki/ofxArtnet)
* on Windows, make sure you have the [K-Lite Codec Pack](http://www.codecguide.com/download_kl.htm) installed to play videos
* for deployment on Windows, the [Visual C++ 2015 Redistributable](https://www.microsoft.com/en-us/download/details.aspx?id=48145)

Hardware

* Artnet-compatible LED controller, e.g. via Enttec ODE

### Setup

* For Artnet, make sure your Ethernet IP address is set to 10.0.0.1 (or whatever MY_IP is defined).

* Disable the Firewall for this app.
