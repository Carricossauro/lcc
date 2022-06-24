import React from "react";

import { useParams } from "react-router-dom";
import Main from "./Main";
import Edit from "./Edit/Edit";

export default function Author({ setShowNavBar, size }) {
  const { authorPath } = useParams();
  switch (authorPath) {
    case "Edit":
      return <Edit size={size} />;
    default:
      return <Main size={size} />;
  }
}
