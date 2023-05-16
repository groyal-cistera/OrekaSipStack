## OrekaSipStack, an opensource VoIP media capture and retrieval platform

Based on [OrecX](http://www.orecx.com/open-source/) [Oreka](https://github.com/OrecX/Oreka), this project tries to provide a complete Call Recording (SIPREC) solution.  

### Components
- **Orkaudio**:  
    The audio capture and storage daemon with pluggable capture modules currently comes with modules for VoIP and sound device recording.
- **Orktrack**:  
    Tracks and publishes all activity from one or more orkaudio services to any mainstream database/storage system.
    

### Building

#### Docker

```bash
export DOCKER_BUILDKIT=1
distribution/docker
docker build -f Dockerfile.orkaudio -t voiceip/orkaudio .
docker run -it --net=host --restart=always --privileged=true -v /var/log/orkaudio:/var/log/orkaudio  -v /etc/orkaudio:/etc/orkaudio voiceip/orkaudio:latest 
```

### Distribution & Installation

#### Docker

Docker container needs at least full access to the hosts network and a mount to the recordings directory to save the recordings, logging files and config files.
/etc/orkaudio
/var/log/orkaudio


```bash
docker run -it --net=host --restart=always --privileged=true -v /var/log/orkaudio:/var/log/orkaudio -v /etc/orkaudio:/etc/orkaudio voiceip/orkaudio:latest
```
