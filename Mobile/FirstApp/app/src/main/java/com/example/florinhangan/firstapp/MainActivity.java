package com.example.florinhangan.firstapp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btnCalculate = (Button)findViewById(R.id.btnCalculate);
        btnCalculate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                EditText txtFirstNumber = (EditText)findViewById(R.id.txtFirstNumber);
                EditText txtSecondNumber = (EditText)findViewById(R.id.txtSecondNumber);
                TextView labelResult = (TextView)findViewById(R.id.labelResult);

                int firstNumber = Integer.parseInt(txtFirstNumber.getText().toString());
                int secondNumber = Integer.parseInt(txtSecondNumber.getText().toString());
                int result = firstNumber + secondNumber;
                labelResult.setText(result + "");
            }
        });
    }
}
