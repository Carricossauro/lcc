import React from "react";

import { useParams } from "react-router-dom";
import AuthorLogin from "./AuthorLogin";

export default function Author({ setShowNavBar, size }) {
  const { authorPath } = useParams();
  switch (authorPath) {
    case "Login":
      setShowNavBar(false);
      return <AuthorLogin size={size} />;
  }
}
