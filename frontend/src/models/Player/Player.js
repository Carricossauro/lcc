import React, { useEffect } from "react";

import { useParams } from "react-router-dom";
import Gamelist from "../Gamelist/Gamelist";
import Game from "./Game/Game";

export default function Player({ setShowNavBar, size, game }) {
    const redirect = (page) => {
        window.location.href = page;
    };

    const { playerPath, gameid } = useParams();

    if (game) {
        return <Game id={gameid} />;
    } else {
        switch (playerPath) {
            case "Main":
                setShowNavBar(true);
                return <Gamelist />;
            default:
                redirect("/Player/Main");
                break;
        }
    }
}
