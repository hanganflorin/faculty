package com.example.florinhangan.expenses;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.EditText;
import android.widget.Toast;

public class AddEditExpenseActivity extends AppCompatActivity {
    public static final String EXTRA_ID =
            "com.example.florinhangan.expenses.EXTRA_ID";
    public static final String EXTRA_TITLE =
            "com.example.florinhangan.expenses.EXTRA_TITLE";
    public static final String EXTRA_DESCRIPTION =
            "com.example.florinhangan.expenses.EXTRA_DESCRIPTION";
    public static final String EXTRA_AMOUNT =
            "com.example.florinhangan.expenses.EXTRA_EXTRA_AMOUNT";


    private EditText editTextTitle;
    private EditText editTextDescription;
    private EditText editTextAmount;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_expense);

        editTextTitle = findViewById(R.id.edit_text_title);
        editTextDescription = findViewById(R.id.edit_text_description);
        editTextAmount = findViewById(R.id.edit_text_amount);

        getSupportActionBar().setHomeAsUpIndicator(R.drawable.ic_close);

        Intent intent = getIntent();
        if (intent.hasExtra(EXTRA_ID)) {
            setTitle("Edit Expense");
            editTextTitle.setText(intent.getStringExtra(EXTRA_TITLE));
            editTextDescription.setText(intent.getStringExtra(EXTRA_DESCRIPTION));
            editTextAmount.setText(intent.getStringExtra(EXTRA_AMOUNT));
        } else {
            setTitle("Add Expense");
        }


    }

    private void saveExpense() {
        String title = editTextTitle.getText().toString().trim();
        String description = editTextDescription.getText().toString().trim();
        int amount = Integer.parseInt(editTextAmount.getText().toString());

        if (title.isEmpty() || description.isEmpty()) {
            Toast.makeText(this, "Please insert a title and a description", Toast.LENGTH_SHORT).show();
            return;
        }

        Intent data = new Intent();
        data.putExtra(EXTRA_TITLE, title);
        data.putExtra(EXTRA_DESCRIPTION, description);
        data.putExtra(EXTRA_AMOUNT, amount);

        int id = getIntent().getIntExtra(EXTRA_ID, -1);
        if ( id != -1 ) {
            data.putExtra(EXTRA_ID, id);
        }

        setResult(RESULT_OK, data);
        finish();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater menuInflater = getMenuInflater();
        menuInflater.inflate(R.menu.add_expense_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.save_expense:
                saveExpense();
            default:
                return super.onOptionsItemSelected(item);

        }
    }
}
