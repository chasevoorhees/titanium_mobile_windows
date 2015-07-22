/**
 * Titanium.UI.TabGroup for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/TabGroup.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/UI/Tab.hpp"
#include "TitaniumWindows/UI/Window.hpp"
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Platform::Collections;
		using namespace Windows::UI::Xaml;
		using namespace Windows::UI::Xaml::Controls;

		TabGroup::TabGroup(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::TabGroup(js_context)
		{
		}

		void TabGroup::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::TabGroup::postCallAsConstructor(js_context, arguments);	

			// root Window object to make layout work
			window__ = js_context.CreateObject(JSExport<TitaniumWindows::UI::Window>::Class()).CallAsConstructor().GetPrivate<TitaniumWindows::UI::Window>();
			window__->setTabGroupContainer(true);

			grid__  = ref new Grid();

#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
			pivot__ = ref new Pivot();

			pivot__->SelectionChanged += ref new SelectionChangedEventHandler([this](Platform::Object^ sender, SelectionChangedEventArgs^ e) {
				TITANIUM_ASSERT(tabs__.size() > pivot__->SelectedIndex);
				set_activeTab(tabs__.at(pivot__->SelectedIndex), false);
			});

			grid__->Children->Append(pivot__);
#else
			sectionView__ = ref new ListView();
			sectionView__->IsItemClickEnabled = true;

			//
			// ListView.ItemContainerStyle
			//
			Platform::String^ style = R"(
<Style xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation" TargetType="ListViewItem">
  <Setter Property="HorizontalContentAlignment" Value="Center" />
  <Setter Property="VerticalContentAlignment" Value="Center" />
  <Setter Property="FontSize" Value="20"/>
</Style>
			)";
			sectionView__->ItemContainerStyle = static_cast<Style^>(Markup::XamlReader::Load(style));

			sectionView__->ItemClick += ref new Controls::ItemClickEventHandler(
				[this](Platform::Object^ sender, Controls::ItemClickEventArgs^ e) {
				const auto listview = safe_cast<Controls::ListView^>(sender);

				uint32_t selectedIndex = -1;
				listview->Items->IndexOf(e->ClickedItem, &selectedIndex);
				if (selectedIndex == -1) return;

				TITANIUM_LOG_WARN(tabs__.size() > selectedIndex);
				set_activeTab(tabs__.at(selectedIndex));
			});

			sectionViewSource__ = ref new Data::CollectionViewSource();
			sectionViewItems__ = ref new Vector<Platform::String^>();
			sectionViewSource__->Source = sectionViewItems__;

			auto binding = ref new Data::Binding();
			binding->Source = sectionViewSource__;
			Data::BindingOperations::SetBinding(sectionView__, Controls::ListView::ItemsSourceProperty, binding);

			const auto col1 = ref new ColumnDefinition();
			const auto col2 = ref new ColumnDefinition();
			const auto row1    = ref new RowDefinition();

			col1->Width = GridLengthHelper::FromValueAndType(0.25, GridUnitType::Star); // 25%
			col2->Width = GridLengthHelper::FromValueAndType(0.75, GridUnitType::Star); // 75%

			grid__->ColumnDefinitions->Append(col1);
			grid__->ColumnDefinitions->Append(col2);
			grid__->RowDefinitions->Append(row1);

			grid__->Children->Append(sectionView__);
			grid__->SetColumn(sectionView__, 0);
			grid__->SetRow(sectionView__, 0);
#endif

			Titanium::UI::TabGroup::setLayoutDelegate<WindowsViewLayoutDelegate>();
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(grid__);

			window__->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->add(get_object().GetPrivate<Titanium::UI::View>());
		}

		void TabGroup::set_activeTab(const std::shared_ptr<Titanium::UI::Tab>& activeTab) TITANIUM_NOEXCEPT
		{
			set_activeTab(activeTab, true);
		}

		void TabGroup::set_activeTab(const std::shared_ptr<Titanium::UI::Tab>& activeTab, bool updateUI) TITANIUM_NOEXCEPT
		{
			if (updateUI && activeTab != activeTab__) {
				const auto tabview = activeTab->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
				pivot__->SelectedItem = tabview;
#else
				if (grid__->Children->Size > 1) {
					grid__->Children->RemoveAt(1);
				}
				grid__->Children->Append(tabview);
				grid__->SetColumn(tabview, 1);
				grid__->SetRow(tabview, 0);
#endif
			}
			Titanium::UI::TabGroup::set_activeTab(activeTab);
		}

		void TabGroup::open() TITANIUM_NOEXCEPT
		{
			window__->open(nullptr);

			if (tabs__.size() > 0) {
				set_activeTab(tabs__.at(0));
			}

			Titanium::UI::TabGroup::open();
		}

		void TabGroup::close() TITANIUM_NOEXCEPT
		{
			Titanium::UI::TabGroup::close();
			window__->close(nullptr);
		}

		void TabGroup::addTab(const std::shared_ptr<Titanium::UI::Tab>& tab) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TabGroup::addTab(tab);
			const auto windows_tab = dynamic_cast<TitaniumWindows::UI::Tab*>(tab.get());
			const auto tabview = windows_tab->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
			if (windows_tab) {
#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
				pivot__->Items->Append(tabview);
#else
				sectionViewItems__->Append(Utility::ConvertUTF8String(windows_tab->get_title()));
#endif
			}
		}

		void TabGroup::JSExportInitialize() 
		{
			JSExport<TabGroup>::SetClassVersion(1);
			JSExport<TabGroup>::SetParent(JSExport<Titanium::UI::TabGroup>::Class());
		}

	}  // namespace UI
}  // namespace TitaniumWindows