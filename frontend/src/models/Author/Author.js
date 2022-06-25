import React from "react";

import { useParams } from "react-router-dom";
import Gamelist from "../Gamelist/Gamelist";
import Main from "./Main";
import Edit from "./Edit/Edit";

export default function Author({ setShowNavBar, size }) {
    const redirect = (page) => {
        window.location.href = page;
    };
    const { authorPath } = useParams();
    switch (authorPath) {
        case "Explore":
            return <Gamelist />;
        case "Mygames":
            return <Gamelist author="sauro" />; // TODO - username guardado
        case "Edit":
            return <Edit size={size} />;
        case "Main":
            return <Main size={size} />;
        default:
            redirect("/Author/Main");
            break;
    }
}
