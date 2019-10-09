
#include "app_options.hpp"
#include "file_saver.hpp"
#include "string_helpers.hpp"

#include "DirectXTex.h"

#include <exception>

namespace {

bool image_needs_converting(const DirectX::ScratchImage& image) noexcept
{
   const auto format = image.GetMetadata().format;

   switch (format) {
   case DXGI_FORMAT_R8G8B8A8_UNORM:
   case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
   case DXGI_FORMAT_B8G8R8A8_UNORM:
   case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
   case DXGI_FORMAT_B8G8R8X8_UNORM:
   case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
      return false;
   default:
      return true;
   }
}

void ensure_basic_format(DirectX::ScratchImage& image)
{
   DirectX::ScratchImage conv_image;

   if (DirectX::IsCompressed(image.GetMetadata().format)) {
      DirectX::Decompress(*image.GetImage(0, 0, 0), DXGI_FORMAT_R8G8B8A8_UNORM,
                          conv_image);

      image = std::move(conv_image);
   }
   else if (image_needs_converting(image)) {
      DirectX::Convert(*image.GetImage(0, 0, 0), DXGI_FORMAT_R8G8B8A8_UNORM,
                       DirectX::TEX_FILTER_DEFAULT, DirectX::TEX_THRESHOLD_DEFAULT,
                       conv_image);

      image = std::move(conv_image);
   }
}

auto image_extension(const Image_format format) noexcept -> std::string_view
{
   switch (format) {
   case Image_format::tga:
      return ".tga"_sv;
   case Image_format::png:
      return ".png"_sv;
   case Image_format::dds:
      return ".dds"_sv;
   default:
      std::terminate();
   }
}

}

void save_image(std::string_view name, DirectX::ScratchImage image,
                File_saver& file_saver, Image_format save_format)
{
   const auto path =
      file_saver.build_file_path("textures"_sv, name, image_extension(save_format));

   file_saver.create_dir("textures"_sv);

   if (save_format == Image_format::tga) {
      ensure_basic_format(image);

      DirectX::SaveToTGAFile(*image.GetImage(0, 0, 0), path.c_str());
   }
   else if (save_format == Image_format::png) {
      ensure_basic_format(image);

      DirectX::SaveToWICFile(*image.GetImage(0, 0, 0), DirectX::WIC_FLAGS_NONE,
                             DirectX::GetWICCodec(DirectX::WIC_CODEC_PNG), path.c_str());
   }
   else if (save_format == Image_format::dds) {
      DirectX::SaveToDDSFile(image.GetImages(), image.GetImageCount(),
                             image.GetMetadata(), DirectX::DDS_FLAGS_NONE, path.c_str());
   }
}
