import React, { useEffect, useState } from "react";

const Expense = () => {
  const [list, setList] = useState(() => {
    return localStorage.getItem("data")
      ? JSON.parse(localStorage.getItem("data"))
      : [];
  });

  useEffect(() => {
    localStorage.setItem("data", JSON.stringify(list));
  }, [list]);

  const [expenseAmount, setExpenseAmount] = useState("");
  const [expenseDesc, setExpenseDesc] = useState("");

  const [incomeDesc, setIncomeDesc] = useState("");
  const [IncomeAmount, setIncomeAmount] = useState("");

  const addIncome = () => {
    if (!incomeDesc || !IncomeAmount) return;

    const newIncome = {
      id: Date.now(),
      desc: incomeDesc,
      amount: parseFloat(IncomeAmount),
      type: "income",
    };

    setList([...list, newIncome]);
    setIncomeDesc("");
    setIncomeAmount("");
  };
  const addExpense = () => {
    if (!expenseDesc || !expenseAmount) return;

    const newExpense = {
      id: Date.now(),
      desc: expenseDesc,
      amount: -parseFloat(expenseAmount),
      type: "expense",
    };

    setList([...list, newExpense]);
    setExpenseDesc(""); // reset the input field
    setExpenseAmount(""); // reset the input field
  };

  // .filter() -> array method which loops through every element of array keeps only those which pass the condition -> returns a new list.
  const deleteExpense = (id) => {
    setList(list.filter((item) => item.id !== id));
  };

  return (
    <div className="container">
      <h1>Expense Tracker</h1>

      {/* Expense Form */}
      <div className="expense">
        <input
          type="text"
          value={expenseDesc}
          placeholder="Enter expense description"
          onChange={(e) => setExpenseDesc(e.target.value)}
        />
        <input
          type="number"
          value={expenseAmount}
          placeholder="Enter expense amount"
          onChange={(e) => setExpenseAmount(e.target.value)}
        />

        <button onClick={addExpense}>Add Expense</button>
      </div>

      {/* Income Form */}
      <div className="income">
        <input
          type="text"
          value={incomeDesc}
          placeholder="Enter income description"
          onChange={(e) => setIncomeDesc(e.target.value)}
        />
        <input
          type="number"
          value={IncomeAmount}
          placeholder="Enter income amount"
          onChange={(e) => setIncomeAmount(e.target.value)}
        />

        <button onClick={addIncome}>Add Income</button>
      </div>

      <ul>
        {list.length > 0 &&
          list.map((item) => (
            <li key={item.id}>
              {item.desc} - ￡{item.amount.toFixed(2)}
              <button onClick={() => deleteExpense(item.id)}>❌</button>
            </li>
          ))}
      </ul>

      <h3>
        Total: ￡
        {list.reduce((total, item) => total + item.amount, 0).toFixed(2)}
      </h3>
    </div>
  );
};

export default Expense;
