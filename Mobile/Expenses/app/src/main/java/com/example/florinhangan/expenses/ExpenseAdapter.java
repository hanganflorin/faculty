package com.example.florinhangan.expenses;

import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

public class ExpenseAdapter extends RecyclerView.Adapter<ExpenseAdapter.ExpenseHolder> {
    private List<Expense> expenses = new ArrayList<>();
    private OnItemClickListener listener;

    @NonNull
    @Override
    public ExpenseHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int i) {
        View itemView = LayoutInflater.from(viewGroup.getContext())
                .inflate(R.layout.expense_item, viewGroup, false);
        return new ExpenseHolder(itemView);
    }

    @Override
    public void onBindViewHolder(@NonNull ExpenseHolder expenseHolder, int i) {
        Expense currentExpense = expenses.get(i);
        expenseHolder.textViewTitle.setText(currentExpense.getTitle());
        expenseHolder.textViewDescription.setText(currentExpense.getDescription());
        expenseHolder.textViewAmount.setText(String.valueOf(currentExpense.getAmount()));
    }

    @Override
    public int getItemCount() {
        return expenses.size();
    }

    public void setExpenses(List<Expense> expenses) {
        this.expenses = expenses;
        notifyDataSetChanged();
    }

    public Expense getExpenseAt(int pos) {
        return expenses.get(pos);
    }

    class ExpenseHolder extends RecyclerView.ViewHolder {
        private TextView textViewTitle;
        private TextView textViewDescription;
        private TextView textViewAmount;

        public ExpenseHolder(@NonNull View itemView) {
            super(itemView);
            textViewTitle = itemView.findViewById(R.id.text_view_title);
            textViewDescription = itemView.findViewById(R.id.text_view_description);
            textViewAmount = itemView.findViewById(R.id.text_view_amount);

            itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    int pos = getAdapterPosition();
                    if (listener != null && pos != -1) {
                        listener.onItemClick(expenses.get(pos));
                    }
                }
            });
        }
    }

    public interface OnItemClickListener {
        void onItemClick(Expense expense);
    }

    public void setonClickItemListener(OnItemClickListener listener) {
        this.listener = listener;
    }
}
