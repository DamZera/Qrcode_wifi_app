import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import qrapp.backend 1.0
import QtQuick.Layouts 1.3

Window {
    id: main
    visible: true
    color: "#ffffff"
    contentOrientation :Qt.PortraitOrientation

    BackEnd {
        id: backend
    }


    ColumnLayout  {
        id: columnLayout
        width: parent.width
        spacing: 20

        Image {
            id: image
            width: 300
            height: 300
            Layout.alignment: Qt.AlignCenter
            anchors.top: parent.top
            anchors.topMargin: 20
            fillMode: Image.PreserveAspectFit
            source: backend.sourceImage
        }

        RowLayout {
            spacing: 20
            Layout.alignment: Qt.AlignCenter
            Layout.topMargin: 20
            Text {
                id: ssid_txt
                width: parent.width
                height: 17
                text: qsTr("SSID")
                font.bold: true
                font.pixelSize: 12
            }

            TextInput {
                id: ssid_input
                width: parent.width
                height: 30
                text: qsTr("ssid")
                renderType: Text.QtRendering
                wrapMode: Text.NoWrap
                selectedTextColor: "#ffffff"
                font.pixelSize: 12
                onTextChanged: backend.ssid = text
            }
        }

        RowLayout {
            spacing: 20
            Layout.alignment: Qt.AlignCenter
            Text {
                id: password_txt
                width: parent.width
                height: 30
                text: qsTr("Password")
                font.bold: true
                font.pixelSize: 12
            }

            TextInput {
                id: password_input
                width: parent.width
                height: 30
                text: qsTr("password")
                echoMode: TextInput.PasswordEchoOnEdit
                font.pixelSize: 12
                onTextChanged: backend.password = text
            }
        }

        Rectangle {
            id: generate_button
            Layout.alignment: Qt.AlignCenter
            width: 200
            height: 30
            color: "#24d0fd"

            Text {
                id: element
                x: 51
                y: 7
                text: qsTr("Generate QrCode")
                font.pixelSize: 12
            }

            MouseArea {
                id: generate_mouseaera
                x: 0
                y: 151
                width: 200
                height: 30
                onClicked: backend.clickOnGenerate()
            }
        }



    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:600;width:800}
}
##^##*/
