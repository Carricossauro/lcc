import { React, useEffect, useState } from "react";
import { useParams } from "react-router-dom";
import Gamelist from "../Gamelist/Gamelist";
import Game from "./Game/Game";
import { confirmType } from "../../API_index";

export default function Player({
    setShowNavBar,
    size,
    game,
    cookies,
    removeCookies,
}) {
    const redirect = (page) => {
        window.location.href = page;
    };

    const { playerPath, gameid } = useParams();

    useEffect(() => {
        async function effect() {
            try {
                const token = cookies["access_token"];
                const c_username = cookies["username"];

                if (!token || !c_username) throw new Error();

                const correctUser = await confirmType(c_username, token, false);

                if (!correctUser) throw new Error();
            } catch (e) {
                redirect("/");
            }
        }
        effect();
    }, []);

    if (game) {
        return <Game id={gameid} cookies={cookies} />;
    } else {
        switch (playerPath) {
            case "Main":
                setShowNavBar(true);
                return (
                    <Gamelist cookies={cookies} removeCookies={removeCookies} />
                );
            default:
                redirect("/Player/Main");
                break;
        }
    }
}
