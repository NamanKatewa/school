import { useState } from "react";
import "./Todo.css";

const Todo = () => {
  const [task, setTask] = useState("");
  const [tasks, setTasks] = useState([]);

  return (
    <div className="todo">
      <h1>Todo</h1>
      <div className="tasks">
        {tasks.map((value, index) => (
          <p key={index}>{value}</p>
        ))}
      </div>

      <div className="add">
        <input
          type="text"
          value={task}
          onChange={(e) => setTask(e.target.value)}
        />
        <button
          onClick={() => {
            setTasks([...tasks, task]);
            setTask("");
          }}
        >
          Add
        </button>
      </div>
    </div>
  );
};

export default Todo;
