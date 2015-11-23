/**
* Titanium.UI.Button for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_BUTTON_HPP_
#define _TITANIUMWINDOWS_UI_BUTTON_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/Button.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.UI.Button implementation for
		  Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT Button final : public Titanium::UI::Button, public JSExport<Button>
		{
		public:
			Button(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Button() = default;
			Button(const Button&) = default;
			Button& operator=(const Button&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Button(Button&&) = default;
			Button& operator=(Button&&) = default;
#endif

			static void JSExportInitialize();
			
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual void set_color(const std::string& color) TITANIUM_NOEXCEPT override final;
			virtual void set_font(const Titanium::UI::Font& font) TITANIUM_NOEXCEPT override final;
			virtual void set_image(const std::string& image) TITANIUM_NOEXCEPT override final;
			virtual void set_textAlign(const Titanium::UI::TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT override final;
			virtual void set_title(const std::string& title) TITANIUM_NOEXCEPT override final;
			virtual void set_verticalAlign(const Titanium::UI::TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT override final;

			static const std::uint32_t DefaultFontSize = 20;

		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::unordered_map<std::string, std::string> custom_fonts__;
#pragma warning(pop)
			Windows::UI::Xaml::Controls::Button^ button__;
		};
	} // namespace UI
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UI_BUTTON_HPP_
