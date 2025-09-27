import React from "react";
import ReactDOM from "react-dom/client";
import "./index.css";
import Expense from "./Expense";

const root = ReactDOM.createRoot(document.getElementById("root"));
root.render(
  <React.StrictMode>
    <Expense />
  </React.StrictMode>
);
