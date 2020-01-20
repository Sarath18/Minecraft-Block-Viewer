# Minecraft Block Viewer
An interactive application developed using OpenGL and C++ to view and interact with Minecraft blocks.

The purpose behind the developement of this project was solely learning Computer Graphics and getting used to the OpenGL library.

#### Features
- Enable/disable lights
- Phong Lighting
- Rendering transparent/translucent object
- Block hover animation
- Multiple texture faces
- Specular and Diffuse maps

#### Build instructions
Run the following script in the project folder to fetch texture atlas
```bash
./fetch_textures.sh
```

Build the project
```bash
mkdir build
cd build
cmake ..
make
```

Run the program
```bash
./minecraft_block_viewer
```

##### Controls
| Key        | Description              |
| ---------- | ------------------------ |
| PageUp     | Switch to next block     |
| PageDown   | Switch to previous Block |
| L Key      | Toggle Lighting in scene |
| Mouse Hold | Break Block              |
| Escape key | Exit                     |
| Arrow Keys | Rotate Block             |