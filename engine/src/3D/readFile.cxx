#include "RipsawEngine/3D/Core/Engine.hxx"

#include <stdexcept>

namespace RipsawEngine::_3D
{

std::string Engine::readFile(const std::string& file)
{
  const char* path = file.c_str();
  SDL_IOStream* io = SDL_IOFromFile(path, "rb");
  if (io == nullptr)
  {
    throw std::runtime_error{
      std::string{"[ERROR] Failed opening file: "} + path + " : " + SDL_GetError()};
  }

  const Sint64 size = SDL_GetIOSize(io);
  if (size < 0)
  {
    SDL_CloseIO(io);
    throw std::runtime_error{"[ERROR] Failed getting file size: " + std::string{path} + " : " + std::string{SDL_GetError()}};
  }

  std::string out;
  out.resize(static_cast<std::size_t>(size));

  std::size_t totalRead = 0;
  while (totalRead < out.size())
  {
    const std::size_t n = SDL_ReadIO(io, out.data() + totalRead, out.size() - totalRead);
    if (n == 0)
    {
      SDL_CloseIO(io);
      throw std::runtime_error{"[ERROR] Failed getting file size: " + std::string{path} + " : " + std::string{SDL_GetError()}};
    }
    totalRead += n;
  }

  SDL_CloseIO(io);
  return out;
}

}

