import "./App.css";

import { useState } from "react";

function App() {
  const [counter, setCounter] = useState(0);
  const [color, setColor] = useState("black");

  return (
    <div className="App">
      <p style={{ color: color }}>{counter}</p>

      <button
        onClick={() => {
          setCounter(counter - 1);
          setColor("red");
        }}
      >
        Decrease
      </button>

      <button
        onClick={() => {
          setCounter(counter + 1);
          setColor("green");
        }}
      >
        Increase
      </button>
    </div>
  );
}

export default App;
