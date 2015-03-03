/**
* Titanium.UI.ImageView for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_IMAGEVIEW_HPP_
#define _TITANIUMWINDOWS_UI_IMAGEVIEW_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include "ViewBase.hpp"
#include <algorithm>
#include <boost/algorithm/string/predicate.hpp>

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.UI.ImageView implementation for
		  Windows.
		*/
// Silence 4275 about ViewBase for now. We need to merge View and ViewBase and then remove this pragma! TIMOB-18422
#pragma warning(push)
#pragma warning(disable : 4275)
		class TITANIUMWINDOWS_UI_EXPORT ImageView final : public Titanium::UI::ImageView, public JSExport<ImageView>, public ViewBase
		{
#pragma warning(pop)
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

			virtual void animate(const JSObject& animation, JSObject& callback, JSObject& this_object) TITANIUM_NOEXCEPT override;

			virtual void set_image(const std::string& image) TITANIUM_NOEXCEPT override final;
			virtual void set_images(const std::vector<std::string>& images) TITANIUM_NOEXCEPT override final;

			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override final;

			virtual void set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT override final;
			virtual void set_height(const std::string& height) TITANIUM_NOEXCEPT override final;
			virtual void set_layout(const std::string& layout) TITANIUM_NOEXCEPT override final;
			virtual void set_left(const std::string& left) TITANIUM_NOEXCEPT override final;
			virtual void set_right(const std::string& right) TITANIUM_NOEXCEPT override final;
			virtual void set_top(const std::string& top) TITANIUM_NOEXCEPT override final;
			virtual void set_width(const std::string& width) TITANIUM_NOEXCEPT override final;

		private:
			Windows::Foundation::EventRegistrationToken internal_load_event_;
			Windows::UI::Xaml::Controls::Image^ image__;
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string path_;
#pragma warning(pop)

			// Event handlers
			Windows::Foundation::EventRegistrationToken click_event_;
			unsigned int click_event_count_{0};
			Windows::Foundation::EventRegistrationToken touch_start_event_;
			unsigned int touch_start_event_count_{0};
			Windows::Foundation::EventRegistrationToken touch_end_event_;
			unsigned int touch_end_event_count_{0};
			Windows::Foundation::EventRegistrationToken touch_move_event_;
			unsigned int touch_move_event_count_{0};
			Windows::Foundation::EventRegistrationToken touch_cancel_event_;
			unsigned int touch_cancel_event_count_{0};
			unsigned int post_layout_event_count_{0};
		};
	} // namespace UI
} // namespace TitaniumWindow

#endif  // _TITANIUMWINDOWS_UI_IMAGEVIEW_HPP_
