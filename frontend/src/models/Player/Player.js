import React, { useEffect } from "react";

import { useParams } from "react-router-dom";
import Main from "./Main";
import Game from "./Game/Game";

export default function Player({ setShowNavBar, size, game }) {
    const { playerPath, gameid } = useParams();

    if (game) {
        return <Game id={gameid} />;
    } else {
        switch (playerPath) {
            default:
                setShowNavBar(true);
                return <Main size={size} />;
        }
    }
}
