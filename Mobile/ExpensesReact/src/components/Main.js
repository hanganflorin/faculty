import React, {Component} from 'react';
import {
    View,
    Text,
    StyleSheet,
    TextInput,
    ScrollView,
    TouchableOpacity, AsyncStorage, Button
} from 'react-native';
import Expense from './Expenses';
import Repository from '../backend/repository'
import AddUpdateExpense from './AddUpdateExpense'

export default class Main extends Component {
    constructor(props) {
        super(props);
        this.state = {
            expensesArray: [],
            isAddEditExpenseVisible: false,
            inputId: null,
            inputTitle: null,
            inputAmount: null,
            inputDescription: null,
        };
        this.refreshData();
    }

    render() {
        let expenses = this.state.expensesArray.map((expense) => {
            return <Expense
                key={expense.id}
                title={expense.title}
                description={expense.description}
                amount={expense.amount}
                deleteMethod={() => this.deleteNote(expense.id)}
                updateMethod={() => this.updateNote(expense)}
            />
        });
        if (this.state.isAddEditExpenseVisible)
            return (
                <View style={styles.container}>
                    <View style={styles.header}>
                        <Text style={styles.headerText}>Expenses</Text>
                    </View>
                    <View style={this.props.style}>
                        <TextInput
                            style={styles.textInputt}
                            onChangeText={(inputTitle) => this.setState({inputTitle})}
                            value={this.state.inputTitle}
                            placeholder={"Title"}
                        />
                        <TextInput
                            style={styles.textInputt}
                            onChangeText={(inputDescription) => this.setState({inputDescription})}
                            value={this.state.inputDescription}
                            placeholder={"Description"}
                        />
                        <TextInput
                            style={styles.textInputt}
                            keyboardType={"numeric"}
                            onChangeText={(inputAmount) => this.setState({inputAmount})}
                            value={this.state.inputAmount}
                            placeholder={"Amount"}
                        />
                        <View style={styles.buttons}>
                            <Button style={styles.button} onPress={this.cancel.bind(this)} title="Cancel"/>
                            <Button style={styles.button} onPress={this.save.bind(this)} title="Save"/>
                        </View>
                    </View>
                </View>
            );
        else
            return (
                <View style={styles.container}>
                    <View style={styles.header}>
                        <Text style={styles.headerText}>Expenses</Text>
                    </View>
                    <ScrollView style={styles.scrollContainer}>
                        {expenses}
                    </ScrollView>
                    <TouchableOpacity onPress={() => this.setVisible(true)} style={styles.addButton}>
                        <Text style={styles.addButtonText}>+</Text>
                    </TouchableOpacity>
                </View>
            );
    }

    async refreshData() {
        let items = await Repository.getAll();
        this.setState({expensesArray: items});
    }

    setVisible(val) {
        this.setState({isAddEditExpenseVisible: val});
    }


    deleteNote(key) {
        Repository.delete({
            id: key
        });
        this.refreshData();
    }

    updateNote(expense) {
        this.setState({
            inputId: expense.id,
            inputTitle: expense.title,
            inputDescription: expense.description,
            inputAmount: expense.amount
        });
        this.setVisible(true);
    }

    cancel() {
        this.setVisible(false);
    }

    save() {
        if ( this.state.inputId != null ) { //add
            Repository.insert({
                title: this.state.inputTitle,
                description: this.state.inputDescription,
                amount: this.state.inputAmount
            });
        }
        else { //update
            Repository.update({
                id: this.state.inputId,
                title: this.state.inputTitle,
                description: this.state.inputDescription,
                amount: this.state.inputAmount
            });
        }
        this.setState({
            inputId: null,
            inputTitle: null,
            inputDescription: null,
            inputAmount: null
        });
        this.setVisible(false);
        this.refreshData();
    }
}
const styles = StyleSheet.create({
    container: {
        flex: 1,
    },
    header: {
        backgroundColor: '#1a6b1a',
        alignItems: 'center',
        justifyContent: 'center',
        borderBottomWidth: 10,
        borderBottomColor: '#ddd'
    },
    headerText: {
        color: 'white',
        fontSize: 20,
        padding: 26,
    },
    scrollContainer: {
        flex: 1,
        marginBottom: 100,
    },
    footer: {
        position: 'absolute',
        bottom: 0,
        left: 0,
        right: 0,
        zIndex: 10
    },
    textInput: {
        alignSelf: 'stretch',
        color: '#fff',
        padding: 20,
        backgroundColor: '#252525',
        borderTopWidth: 2,
        borderTopColor: '#ededed'
    },
    addButton: {
        position: 'absolute',
        zIndex: 11,
        right: 20,
        bottom: 20,
        backgroundColor: '#E91E63',
        width: 70,
        height: 70,
        borderRadius: 35,
        alignItems: 'center',
        justifyContent: 'center',
        elevation: 8
    },
    addButtonText: {
        color: '#fff',
        fontSize: 24
    },
    addUpdateExpense: {},
    textInputt: {
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