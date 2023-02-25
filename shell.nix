with import <nixpkgs> {};
stdenv.mkDerivation {
    name = "env";
    nativeBuildInputs = [pkg-config];
    buildInputs = [
    gcc
    meson
    ninja
    glfw
    cglm
    ];
  }
