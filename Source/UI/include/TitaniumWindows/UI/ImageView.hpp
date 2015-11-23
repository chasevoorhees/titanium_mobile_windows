/**
* Titanium.UI.ImageView for Windows
*
* Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_IMAGEVIEW_HPP_
#define _TITANIUMWINDOWS_UI_IMAGEVIEW_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/ImageView.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		class TITANIUMWINDOWS_UI_EXPORT WindowsImageViewLayoutDelegate : public WindowsViewLayoutDelegate {
		public:
			WindowsImageViewLayoutDelegate() TITANIUM_NOEXCEPT;
			virtual ~WindowsImageViewLayoutDelegate();

			void stretchImageView() TITANIUM_NOEXCEPT;

			virtual void set_width(const std::string& width) TITANIUM_NOEXCEPT override;
			virtual void set_height(const std::string& height) TITANIUM_NOEXCEPT override;
		private:
		};

		/*!
		  @class

		  @discussion This is the Titanium.UI.ImageView implementation for
		  Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT ImageView final : public Titanium::UI::ImageView, public JSExport<ImageView>
		{
		public:
			ImageView(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ImageView() = default;
			ImageView(const ImageView&) = default;
			ImageView& operator=(const ImageView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ImageView(ImageView&&) = default;
			ImageView& operator=(ImageView&&) = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			// Methods
			virtual void pause() TITANIUM_NOEXCEPT override final;
			virtual void resume() TITANIUM_NOEXCEPT override final;
			virtual void start() TITANIUM_NOEXCEPT override final;
			virtual void stop() TITANIUM_NOEXCEPT override final;

			// properties
			virtual bool get_animating() const TITANIUM_NOEXCEPT override final;
			virtual void set_image(const std::string& image) TITANIUM_NOEXCEPT override final;
			virtual void set_images(const std::vector<std::string>& images) TITANIUM_NOEXCEPT override final;
			virtual bool get_paused() const TITANIUM_NOEXCEPT override final;

		private:
			Windows::Foundation::EventRegistrationToken internal_load_event_;
			Windows::UI::Xaml::Controls::Image^ image__;
			Windows::UI::Xaml::Media::Animation::Storyboard^ storyboard__;

			bool is_animating__;
			bool is_paused__;
		};
	} // namespace UI
} // namespace TitaniumWindow

#endif  // _TITANIUMWINDOWS_UI_IMAGEVIEW_HPP_
