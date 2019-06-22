/*
    Borealis, a Nintendo Switch UI Library
    Copyright (C) 2019  natinusala

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <BoxLayout.hpp>
#include <Label.hpp>
#include <Rectangle.hpp>

#define LIST_ITEM_VALUE_ANIMATION 100

// A list item
// TODO: Use a Label with integrated ticker
class ListItem : public View
{
    private:
        string label;
        string value;
        bool valueFaint;

        string oldValue;
        bool oldValueFaint;
        float valueAnimation = 0.0f;

        bool drawTopSeparator = true;

        Label *sublabelView = nullptr;

        EventListener clickListener = nullptr;

        void resetValueAnimation();

    public:
        ListItem(string label, string sublabel = "");

        void draw(NVGcontext *vg, int x, int y, unsigned width, unsigned height, Style *style, FrameContext *ctx) override;
        View* requestFocus(FocusDirection direction, View *oldFocus, bool fromUp) override;
        void layout(NVGcontext *vg, Style *style, FontStash *stash) override;
        void getHighlightInsets(unsigned *top, unsigned *right, unsigned *bottom, unsigned *left) override;
        void setParent(View *parent) override;
        bool onClick() override;

        bool hasSubLabel();
        void setDrawTopSeparator(bool draw);

        /**
         * Sets the value of this list item
         * (the text on the right)
         * Set faint to true to have the new value
         * use a darker color (typically "OFF" labels)
         */
        void setValue(string value, bool faint = false);

        void setClickListener(EventListener listener);

        ~ListItem();
};

#define TOGGLE_LIST_ITEM_ON     "ON"
#define TOGGLE_LIST_ITEM_OFF    "OFF"

// Some spacing (to make groups of ListItems)
class ListItemGroupSpacing : public Rectangle
{
    public:
        ListItemGroupSpacing(bool separator = false);
};

// A list item with a ON/OFF value
// that can be toggled
// Use the clickListener to detect when the value
// changes
// TODO: Add the ability to change "ON" and "OFF" strings
// TODO: Animate value changes
class ToggleListItem : public ListItem
{
    private:
        bool toggleState;

        void updateValue();

    public:
        ToggleListItem(string label, bool initialValue, string sublabel = "");

        bool onClick() override;
};

// A vertical list of various widgets, with proper margins and spacing
// and a scroll bar
class List : public BoxLayout
{
    public:
        List();

        View* defaultFocus(View *oldFocus) override;

    protected:
        void customSpacing(View *current, View *next, int *spacing) override;
};