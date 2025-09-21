import QtQuick 6.4
import QtQuick.Controls 6.4
import QtQml.Models

import com.chordless.chord_observer 1.0
import com.chordless.note_observer 1.0
import com.chordless.settings 1.0

Rectangle {
    required property ChordObserver chord_obs
    required property FullVoicingObserver note_obs
    required property Settings settings

    id: rectangle
    width: 600
    height: 280

    Flow {
        id: flow1
        x: 0
        y: 0
        width: 600
        height: 280

        Row {
            id: row
            width: 580
            height: 64

            ComboBox {
                id: sharpsComboBox
		height: 32
                width: 48
                font.pointSize: 16
                editable: false
                hoverEnabled: true
                ToolTip.delay: 700
                ToolTip.timeout: 4000
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Prefer sharps or flats")
		textRole: "text"
		valueRole: "value"
		onActivated: {
		    settings.sharp = currentValue;
		    note_obs.SetSharp(currentValue);
		    chord_obs.SetSharp(currentValue);
		}
		Component.onCompleted: currentIndex = indexOfValue(settings.sharp)
		model: [{value: true, text: qsTr("♯")}, {value: false, text: qsTr("♭")}]
            }

            CheckBox {
                id: octaveCheckBox
		visible: true
                text: qsTr("Octave")
                checked: note_obs.showOctave
                onCheckedChanged: note_obs.setShowOctave(checked)
                hoverEnabled: true
                ToolTip.delay: 700
                ToolTip.timeout: 4000
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Display note octave as a numeric subscript")
            }

            CheckBox {
                id: bestChordOnlyCheckBox
                visible: true
                text: qsTr("Best Only")
                checked: settings.bestChordOnly
                onCheckedChanged: {
                    settings.bestChordOnly = checked;
                    chord_obs.SetBestChordOnly(checked);
                }
                hoverEnabled: true
                ToolTip.delay: 700
                ToolTip.timeout: 4000
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Show only the best chord match instead of all matches")
            }

            CheckBox {
                id: sustainCheckBox
		visible: false
                text: qsTr("Sustain Pedal")
                hoverEnabled: true
                ToolTip.delay: 700
                ToolTip.timeout: 4000
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Hold notes while sustain pedal is pressed")
            }

            CheckBox {
                id: bassOnlyCheckBox
		visible: false
                text: qsTr("Bass Only")
                hoverEnabled: true
                ToolTip.delay: 700
                ToolTip.timeout: 4000
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Match chords only in the lowest octave")
            }
        }

        Text {
            id: allNotesText
            width: 55
            height: 24
            text: qsTr("All Notes")
            font.pixelSize: 12
        }

        Label {
            id: notesLabel
            width: 500
            height: 59
            text: note_obs.text
            font.pointSize: 24
            font.family: "Helvetica"
        }

        Text {
            id: chordsText
            width: 71
            height: 24
            text: qsTr("Chords")
            font.pixelSize: 12
        }

        Label {
            id: chordsLabel
            width: 500
            height: 59
            text: chord_obs.text
            font.pointSize: 24
            font.family: "Helvetica"
        }
    }
}

