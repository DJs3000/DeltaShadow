{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = [ pkgs.cmake pkgs.clang pkgs.SDL pkgs.SDL_gfx pkgs.SDL_image pkgs.SDL_mixer ];
}
