#include "pch.h"
#include "RenderTree.h"
#include <resvg.h>

namespace resvg
{
	bool RenderTree::Parse(char const* data, uintptr_t length, resvg_options const* options) noexcept
	{
		resvg_render_tree* newTree = nullptr;
		auto const err = resvg_parse_tree_from_data(data, length, options, &newTree);
		if (err != RESVG_OK || !newTree)
			return false;
		if (auto oldTree = std::exchange(m_tree, newTree))
			resvg_tree_destroy(oldTree);
		return true;
	}

	std::vector<uint8_t> RenderTree::Render(float scale, uint32_t width, uint32_t height)
	{
		resvg_transform transform = resvg_transform_identity();
		transform.a = scale;
		transform.d = scale;

		std::vector<uint8_t> pixels(static_cast<size_t>(width) * height * 4, 0);
		resvg_render(
			m_tree,
			transform,
			width,
			height,
			reinterpret_cast<char*>(pixels.data())
		);
		return pixels;
	}

	resvg_size RenderTree::GetSize() const noexcept
	{
		return resvg_get_image_size(m_tree);
	}

	RenderTree::~RenderTree()
	{
		if (m_tree)
			resvg_tree_destroy(m_tree);
	}
}