package com.example.florinhangan.expenses;

import android.arch.persistence.room.Entity;
import android.arch.persistence.room.PrimaryKey;

import java.util.Date;

@Entity(tableName = "expense_table")
public class Expense  {

    @PrimaryKey(autoGenerate = true)
    private int id;
    private String title;
    private String description;
    private int amount;

    public Expense(String title, String description, int amount) {
        this.title = title;
        this.description = description;
        this.amount = amount;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }

    public int getAmount() {
        return amount;
    }

    public String getDescription() {

        return description;
    }

}
