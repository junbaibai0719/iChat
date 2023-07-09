import QtQuick
import QtQuick.Controls
import QtMultimedia

Item {
    id: player
    anchors.margins: 40
    anchors.fill: parent
    property bool isPlaying: false
    signal playing
    signal pausing
    signal forward(int x)
    signal backOff(int x)

    Row {
        id: toobar
        Button {
            id: play
            text: isPlaying ? qsTr("暂停") : qsTr("播放")
            onClicked: {
                if (isPlaying) {
                    isPlaying = false
                    pausing()
                } else {
                    isPlaying = true
                    playing()
                }
            }
        }
        Button {
            id: backBtn
            text: qsTr("-1")
            onClicked: backOff(16)
        }
        Button {
            id: forwardBtn
            text: qsTr("+1")
            onClicked: forward(16)
        }
    }

    GridView {
        id: videoView
        anchors.topMargin: toobar.height
        anchors.fill: parent
        model: ["file:resources/cyberpunk delorean by visualdon 4K.mp4",
            "file:resources/cyberpunk delorean by visualdon 4K.mp4",
            "file:resources/cyberpunk delorean by visualdon 4K.mp4",
            "file:resources/cyberpunk delorean by visualdon 4K.mp4",
            "file:resources/cyberpunk delorean by visualdon 4K.mp4",
            "file:resources/cyberpunk delorean by visualdon 4K.mp4"]
        cellWidth: width / 3
        cellHeight: height / 2

        delegate: Rectangle {
            implicitWidth: GridView.view.cellWidth
            implicitHeight: GridView.view.cellHeight
            Text {
                id: videoTxt
                text: modelData
            }
            Video {
                id: videoPlayer
                anchors.fill: parent
                anchors.topMargin: videoTxt.height
                source: modelData
                Keys.onSpacePressed: video.playbackState
                                     === MediaPlayer.PlayingState ? videoPlayer.pause(
                                                                        ) : videoPlayer.play()
                Keys.onLeftPressed: videoPlayer.position = videoPlayer.position - 5000
                Keys.onRightPressed: videoPlayer.position = videoPlayer.position + 5000
            }

            Connections {
                target: player
                function onPlaying() {
                    videoPlayer.play()
                }
                function onPausing() {
                    videoPlayer.pause()
                }
                function onForward(x) {
                    videoPlayer.position += x
                }
                function onBackOff(x) {
                    videoPlayer.position -= x
                }
            }
        }
    }
}
