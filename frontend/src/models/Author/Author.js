import React from "react";

import { useParams } from "react-router-dom";
import Main from "./Main";
import Edit from "./Edit/Edit";

export default function Author({ setShowNavBar, size }) {
    const redirect = (page) => {
        window.location.href = page;
    };
    const { authorPath } = useParams();
    console.log(useParams());
    switch (authorPath) {
        case "Edit":
            return <Edit size={size} />;
        case "Main":
            return <Main size={size} />;
        default:
            redirect("/Author/Main");
            break;
    }
}
