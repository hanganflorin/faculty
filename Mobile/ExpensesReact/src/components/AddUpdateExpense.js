import React, {Component} from 'react';
import {
    View,
    Text,
    StyleSheet,
    TextInput,
    ScrollView,
    TouchableOpacity, AsyncStorage,
    Button
} from 'react-native';

export default class AddUpdateExpense extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <View style={this.props.style}>
                <TextInput
                    style={styles.textInput}
                    //value={this.state.text}
                    placeholder={"Title"}
                />
                <TextInput
                    style={styles.textInput}
                    //value={this.state.text}
                    placeholder={"Description"}
                />
                <TextInput
                    style={styles.textInput}
                    keyboardType={"numeric"}
                    //value={this.state.text}
                    placeholder={"Amount"}
                />
                <View style={styles.buttons}>
                    <Button style={styles.button} onPress={this.cancel.bind(this)} title="Cancel"/>
                    <Button style={styles.button} onPress={this.save.bind(this)} title="Save"/>
                </View>
            </View>

        );
    }

    cancel() {
        this.props.setVisible(true);
    }

    save() {
        this.props.setVisible(false);
    }


}
const styles = StyleSheet.create({
    textInput: {
        margin: 20,
        height: 40,
        borderColor: '#7a42f4',
        borderWidth: 1
    },
    buttons: {
        margin: 50,
        flex: 1,
        flexDirection: 'row',
        alignItems: 'center',
        justifyContent: 'center',
    },
    button: {
        flex: 1,
    }
});