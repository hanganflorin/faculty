package com.example.florinhangan.expenses;

import android.app.Application;
import android.arch.lifecycle.AndroidViewModel;
import android.arch.lifecycle.LiveData;
import android.support.annotation.NonNull;

import java.util.List;

public class ExpenseViewModel extends AndroidViewModel {
    private ExpenseRepository repository;
    private LiveData<List<Expense>> allExpenses;

    public ExpenseViewModel(@NonNull Application application) {
        super(application);
        repository = new ExpenseRepository(application);
        allExpenses = repository.getAllExpenses();
    }

    public void insert(Expense expense){
        repository.insert(expense);
    }

    public void update(Expense expense){
        repository.update(expense);
    }

    public void delete(Expense expense){
        repository.delete(expense);
    }

    public void deleteAllExpenses(){
        repository.deleteAllExpenses();
    }

    public LiveData<List<Expense>> getAllExpenses() {
        return allExpenses;
    }
}
