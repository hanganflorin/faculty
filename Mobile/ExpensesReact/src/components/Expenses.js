import React, {Component} from 'react';
import {
    View,
    Text,
    StyleSheet,
    TouchableOpacity,
} from 'react-native';


export default class Note extends Component {
    render() {
        return (
            <View key={this.props.id} style={styles.view}>
                <Text style={styles.textTitle}>{this.props.title}</Text>
                <Text style={styles.textDescription}>{this.props.description}</Text>
                <Text style={styles.textAmount}>{this.props.amount}</Text>
                <TouchableOpacity onPress={this.props.deleteMethod} style={styles.buttonDelete}>
                    <Text style={styles.noteDeleteText}>X</Text>
                </TouchableOpacity>
                <TouchableOpacity onPress={this.props.updateMethod} style={styles.buttonUpdate}>
                    <Text style={styles.noteUpdateText}>Update</Text>
                </TouchableOpacity>
            </View>
        );
    }
}
const styles = StyleSheet.create({
    view: {
        position: 'relative',
        padding: 20,
        paddingRight: 100,
        borderBottomWidth: 2,
        borderBottomColor: '#ededed',
    },
    textTitle: {
        fontSize: 24
    },
    textDescription: {
        fontSize: 15
    },
    textAmount: {
        fontSize: 20,
        textAlign: 'right',
        position: 'absolute',
        padding: 10,
        top: 10,
        bottom: 10,
        right: 40
    },
    buttonDelete: {
        position: 'absolute',
        justifyContent: 'center',
        alignItems: 'center',
        backgroundColor: '#b90005',
        padding: 10,
        top: 10,
        bottom: 10,
        right: 10
    },
    noteDeleteText: {
        color: 'white'
    },
    noteUpdateText: {
        color: '#fff232',
    },
    buttonUpdate: {
        // position: 'absolute',
        // justifyContent: 'center',
        // alignItems: 'center',
        backgroundColor: 'white',

        // padding: 10,
        // top: 10,
        // bottom: 10,
        // right: 10
    }
});