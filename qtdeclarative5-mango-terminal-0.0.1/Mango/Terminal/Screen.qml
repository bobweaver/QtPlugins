/*
* Joseph Mills
*/

import QtQuick 2.0
import QtQuick.Controls 1.2

import Mango.Terminal 0.1 as MangoTerm

MangoTerm.TerminalScreen {
    id: screenItem

    property font font
    property real fontWidth: fontMetricText.paintedWidth
    property real fontHeight: fontMetricText.paintedHeight

//    font:    screen.platformName !== "cocoa" ? "monospace" : "menlo"
    anchors.fill: parent
    focus: true

    Component {
        id: textComponent
        MangoTerm.Text {
        }
    }
    Component {
        id: cursorComponent
        MangoTerm.Cursor {
        }
    }
    Action {
        id: copyAction
        shortcut: "Ctrl+Shift+C"
        onTriggered: screen.selection.sendToClipboard()
    }
    Action {
        id: paseAction
        shortcut: "Ctrl+Shift+V"
        onTriggered: screen.selection.pasteFromClipboard()
    }

    onActiveFocusChanged: {
        if (activeFocus) {
            Qt.inputMethod.show();
        }
    }

    Keys.onPressed: {
        if (event.text === "?") {
            screen.printScreen()
        }
        screen.sendKey(event.text, event.key, event.modifiers);
    }

    Text {
        id: fontMetricText
        text: "B"
        font: parent.font
        visible: false
        textFormat: Text.PlainText
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: screen.defaultBackgroundColor
    }
    Flickable {
        id: flickable
        anchors.top: parent.top
        anchors.left: parent.left
        contentWidth: width
        contentHeight: textContainer.height
        interactive: true
        flickableDirection: Flickable.VerticalFlick
        contentY: ((screen.contentHeight - screen.height) * screenItem.fontHeight)

        Item {
            id: textContainer
            width: parent.width
            height: screen.contentHeight * screenItem.fontHeight

            Selection {
                characterHeight: fontHeight
                characterWidth: fontWidth
                screenWidth: screenItem.width

                startX: screen.selection.startX
                startY: screen.selection.startY

                endX: screen.selection.endX
                endY: screen.selection.endY

                visible: screen.selection.enable
            }
        }

        Item {
            id: cursorContainer
            width: textContainer.width
            height: textContainer.height
        }


        onContentYChanged: {
            if (!atYEnd) {
                var top_line = Math.floor(Math.max(contentY,0) / screenItem.fontHeight);
                screen.ensureVisiblePages(top_line);
            }
        }
    }

    Connections {
        id: connections

        target: screen

        onFlash: {
            flashAnimation.start()
        }

        onReset: {
            resetScreenItems();
        }

        onTextCreated: {
            var textSegment = textComponent.createObject(screenItem,
                {
                    "parent" : textContainer,
                    "objectHandle" : text,
                    "font" : screenItem.font,
                    "fontWidth" : screenItem.fontWidth,
                    "fontHeight" : screenItem.fontHeight,
                });
        }

        onCursorCreated: {
            if (cursorComponent.status != Component.Ready) {
                console.log(cursorComponent.errorString());
                return;
            }
            var cursorVariable = cursorComponent.createObject(screenItem,
                {
                    "parent" : cursorContainer,
                    "objectHandle" : cursor,
                    "fontWidth" : screenItem.fontWidth,
                    "fontHeight" : screenItem.fontHeight,
                })
        }

        onRequestHeightChange: {
            terminalWindow.height = newHeight * screenItem.fontHeight;
            terminalWindow.contentItem.height = newHeight * screenItem.fontHeight;
        }

        onRequestWidthChange: {
            terminalWindow.width = newWidth * screenItem.fontWidth;
            terminalWindow.contentItem.width = newWidth * screenItem.fontWidth;
        }
    }

    onFontChanged: {
        setTerminalHeight();
        setTerminalWidth();
    }

    onWidthChanged: {
        setTerminalWidth();
    }
    onHeightChanged: {
        setTerminalHeight();
    }

    Component.onCompleted: {
        setTerminalWidth();
        setTerminalHeight();
    }

    function setTerminalWidth() {
        if (fontWidth > 0) {
            var pty_width = Math.floor(width / fontWidth);
            flickable.width = pty_width * fontWidth;
            screen.width = pty_width;
        }
    }

    function setTerminalHeight() {
        if (fontHeight > 0) {
            var pty_height = Math.floor(height / fontHeight);
            flickable.height = pty_height * fontHeight;
            screen.height = pty_height;
        }
    }

    Rectangle {
        id: flash
        z: 1.2
        anchors.fill: parent
        color: "grey"
        opacity: 0
        SequentialAnimation {
            id: flashAnimation
            NumberAnimation {
                target: flash
                property: "opacity"
                to: 1
                duration: 75
            }
            NumberAnimation {
                target: flash
                property: "opacity"
                to: 0
                duration: 75
            }
        }
    }

    MouseArea {
        id:mousArea

        property int drag_start_x
        property int drag_start_y

        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.MiddleButton
        onPressed: {
            if (mouse.button == Qt.LeftButton) {
                hoverEnabled = true;
                var transformed_mouse = mapToItem(textContainer, mouse.x, mouse.y);
                var character = Math.floor((transformed_mouse.x / fontWidth));
                var line = Math.floor(transformed_mouse.y / fontHeight);
                var start = Qt.point(character,line);
                drag_start_x = character;
                drag_start_y = line;
                screen.selection.startX = character;
                screen.selection.startY = line;
                screen.selection.endX = character;
                screen.selection.endY = line;
            }
        }

        onPositionChanged: {
            var transformed_mouse = mapToItem(textContainer, mouse.x, mouse.y);
            var character = Math.floor(transformed_mouse.x / fontWidth);
            var line = Math.floor(transformed_mouse.y / fontHeight);
            var current_pos = Qt.point(character,line);
            if (line < drag_start_y || (line === drag_start_y && character < drag_start_x)) {
                screen.selection.startX = character;
                screen.selection.startY = line;
                screen.selection.endX = drag_start_x;
                screen.selection.endY = drag_start_y;
            } else {
                screen.selection.startX = drag_start_x;
                screen.selection.startY = drag_start_y;
                screen.selection.endX = character;
                screen.selection.endY = line;
            }
        }

        onReleased: {
            if (mouse.button == Qt.LeftButton) {
                hoverEnabled = false;
                screen.selection.sendToSelection();
            }
        }

        onClicked: {
            if (mouse.button == Qt.MiddleButton) {
                screen.pasteFromSelection();
            }
        }

        onDoubleClicked: {
            if (mouse.button == Qt.LeftButton) {
                var transformed_mouse = mapToItem(textContainer, mouse.x, mouse.y);
                var character = Math.floor(transformed_mouse.x / fontWidth);
                var line = Math.floor(transformed_mouse.y / fontHeight);
                screen.doubleClicked(character,line);
            }
        }
    }
}
