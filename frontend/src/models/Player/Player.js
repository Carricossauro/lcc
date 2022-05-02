import React from "react";

import { useParams } from "react-router-dom";
import PlayerLogin from "./PlayerLogin";

export default function Player({ setShowNavBar, size }) {
  const { playerPath } = useParams();
  switch (playerPath) {
    case "Login":
      setShowNavBar(false);
      return <PlayerLogin size={size} />;
  }
}
