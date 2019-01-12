import {AsyncStorage} from "react-native"


class Repository {
    static KEY = "abcdefghh";

    static async getAll() {
        let result = [];
        const keys = await AsyncStorage.getAllKeys();
        const filteredKeys = keys.filter(key => key.startsWith(Repository.KEY));
        const items = await AsyncStorage.multiGet(filteredKeys);
        items.map(i => result.push(JSON.parse(i[1])));
        return result;
    }

    static async insert(expense) {
        const uniqueId = new Date().valueOf().toString();
        expense.id = uniqueId;
        AsyncStorage.setItem(Repository.KEY + uniqueId, JSON.stringify(expense));
    }

    static update(expense) {
        AsyncStorage.setItem(Repository.KEY + expense.id, JSON.stringify(expense));
    }

    static delete(expense) {
        AsyncStorage.removeItem(Repository.KEY + expense.id)
    }
}

export default Repository;