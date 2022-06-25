import { React, useState, useEffect } from "react";
import ReactDOM from "react-dom";
import "./index.css";
import LoginPopUp from "./models/LoginPopUp/LoginPopUp";
import NavBar from "./models/NavBar/NavBar";
import SignUp from "./models/SignUp/SignUp";
import Login from "./models/Login/Login";
import { BrowserRouter as Router, Route, Routes } from "react-router-dom";
import Player from "./models/Player/Player";
import Author from "./models/Author/Author";
import About from "./models/About/About";
import { useCookies } from "react-cookie";

const Index = () => {
    const [size, setSize] = useState(window.innerWidth);
    const [loginPopUp, setLoginPopUp] = useState(false);
    const [showNavBar, setShowNavBar] = useState(true);
    const [isAuthor, setIsAuthor] = useState(false);

    const [cookies, setCookie] = useCookies(["user"]);

    const checkSize = () => {
        setSize(window.innerWidth);
    };

    const changePopUpState = () => {
        setLoginPopUp((state) => {
            return !state;
        });
    };
    useEffect(() => {
        window.addEventListener("resize", checkSize);
        return () => {
            window.removeEventListener("resize", checkSize);
        };
    }, []);

    return (
        <div>
            <Router>
                {showNavBar && (
                    <NavBar
                        size={size}
                        setPopUp={changePopUpState}
                        setCookie={setCookie}
                        cookies={cookies}
                    />
                )}
                <Routes>
                    <Route
                        path="/Player/Game/:gameid"
                        element={
                            <Player
                                setShowNavBar={setShowNavBar}
                                size={size}
                                game={true}
                            />
                        }
                    ></Route>
                    <Route
                        path="/Player/:playerPath"
                        element={
                            <Player
                                setShowNavBar={setShowNavBar}
                                size={size}
                                game={false}
                            />
                        }
                    ></Route>
                    <Route
                        path="/Author/:authorPath"
                        element={
                            <Author setShowNavBar={setShowNavBar} size={size} />
                        }
                    ></Route>
                    <Route
                        path="/Login"
                        element={
                            <Login
                                setShowNavBar={setShowNavBar}
                                size={size}
                                setIsAuthor={setIsAuthor}
                                isAuthor={isAuthor}
                                setCookie={setCookie}
                                cookies={cookies}
                            />
                        }
                    ></Route>
                    <Route
                        path="/SignUp"
                        element={
                            <SignUp
                                setShowNavBar={setShowNavBar}
                                size={size}
                                setIsAuthor={setIsAuthor}
                                isAuthor={isAuthor}
                                setCookie={setCookie}
                                cookies={cookies}
                            />
                        }
                    ></Route>
                    <Route path="/About" element={<About />}></Route>
                </Routes>
            </Router>
        </div>
    );
};

ReactDOM.render(
    <>
        <Index />
    </>,

    document.getElementById("root")
);
