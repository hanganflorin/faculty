import React from 'react';
import {StyleSheet, Text, View, Button, Vibration} from 'react-native';

export default class App extends React.Component {
    render() {
        return (
            <View style={styles.container}>
                <Button
                    onPress={() => {
                        const PATTERN = [0, 50, 20];
                        Vibration.vibrate(PATTERN, true)
                    }}
                    title="Learn More"
                    color="#841584"
                />
            </View>
        );
    }
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: '#fff',
        alignItems: 'center',
        justifyContent: 'center',
    },
});
