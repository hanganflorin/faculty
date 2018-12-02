package com.example.florinhangan.expenses;

import android.arch.persistence.db.SupportSQLiteDatabase;
import android.arch.persistence.room.Database;
import android.arch.persistence.room.Room;
import android.arch.persistence.room.RoomDatabase;
import android.content.Context;
import android.os.AsyncTask;
import android.support.annotation.NonNull;


@Database(entities = {Expense.class}, version = 1)
public abstract class ExpenseDatabase extends RoomDatabase {

    private static ExpenseDatabase instance;

    public abstract ExpenseDao expenseDao();

    public static synchronized ExpenseDatabase getInstance(Context context) {
        if (instance == null) {
            instance = Room.databaseBuilder(context.getApplicationContext(),
                    ExpenseDatabase.class, "expense_database")
                    .addCallback(roomCallback)
                    .fallbackToDestructiveMigration()
                    .build();
        }
        return instance;
    }

    private static RoomDatabase.Callback roomCallback = new RoomDatabase.Callback() {
        @Override
        public void onCreate(@NonNull SupportSQLiteDatabase db) {
            super.onCreate(db);
            new PopulateDbAsyncTask(instance).execute();
        }
    };

    private static class PopulateDbAsyncTask extends AsyncTask<Void, Void, Void> {
        private ExpenseDao expenseDao;

        private PopulateDbAsyncTask(ExpenseDatabase expenseDatabase) {
            this.expenseDao = expenseDatabase.expenseDao();
        }

        @Override
        protected Void doInBackground(Void... voids) {
            expenseDao.insert(new Expense("Alcoale", "Am baut", 70));
            expenseDao.insert(new Expense("Mancare", "Am mancat", 20));
            expenseDao.insert(new Expense("Beri", "M-am imbatat", 20));
            expenseDao.insert(new Expense("Pacanele", "N-au venit septarii", 100));
            return null;
        }
    }
}
