import { React, useState, useEffect } from "react";
import "./NavBar.css";

import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faBrain, faBars } from "@fortawesome/free-solid-svg-icons";

export default function NavBar(props) {
    const [expanded, setExpanded] = useState(false);

    useEffect(() => {
        if (props.size >= 1024) setExpanded(false);
    }, [props.size]);

    const changeExpanded = () => {
        setExpanded((state) => {
            return !state;
        });
    };

    const redirect = (page) => {
        window.location.href = page;
    };

    return (
        <div className="fixed top-0 left-0 h-16 w-screen bg-color5 flex flex-wrap text-white shadow-md">
            <div className="w-full h-16 lg:w-2/5 h-inherit flex items-center pl-2">
                <button
                    className="flex items-center"
                    onClick={() => redirect("/")}
                >
                    <FontAwesomeIcon icon={faBrain} className="icon" />
                    <span className="ml-2 text-[30px] titleFont font-normal">
                        Computational Mind
                    </span>
                </button>
                <div className="lg:invisible flex justify-end items-center w-1/3 lg:w-0 cursor-pointer">
                    <button onClick={changeExpanded}>
                        <FontAwesomeIcon
                            icon={faBars}
                            className="icon-bars mr-2 hover:text-color1 duration-500"
                        />
                    </button>
                </div>
            </div>
            {props.size >= 1024 && (
                <div className="w-3/5 h-inherit flex flex-wrap justify-end items-center">
                    <div className="flex justify-center mx-3">
                        <button
                            className="flex items-center justify-center px-5 h-9 hover:bg-color1 rounded cursor-pointer duration-1000"
                            onClick={() => redirect("/About")}
                        >
                            ABOUT US
                        </button>
                    </div>
                    <div className="flex justify-center mx-3">
                        <button className="flex items-center justify-center px-5 h-9 hover:bg-color1 rounded cursor-pointer duration-1000">
                            CONTACT
                        </button>
                    </div>
                    <div className="flex justify-center mx-3">
                        <button
                            className="flex items-center justify-center px-5 h-9 hover:bg-color1 rounded cursor-pointer duration-1000"
                            onClick={() => redirect("/SignUp")}
                        >
                            REGISTER
                        </button>
                    </div>
                    <div className="flex justify-center mx-3 mr-6">
                        <button
                            className="flex items-center justify-center w-24 h-9 bg-color1 rounded cursor-pointer hover:text-color4 hover:font-bold duration-1000"
                            onClick={() => redirect("/Login")}
                        >
                            LOGIN
                        </button>
                    </div>
                </div>
            )}
            {props.size < 1024 && (
                <div
                    className={`w-56 h-screen flex flex-col bg-color3 justify-start items-center absolute top-16 right-0 shadow-md duration-1000 ${
                        expanded ? "translate-x-0" : "translate-x-full"
                    }`}
                >
                    <div className="flex justify-center my-3">
                        <button className="flex items-center justify-center h-9 w-32 hover:bg-color1 rounded cursor-pointer duration-1000">
                            ABOUT US
                        </button>
                    </div>
                    <div className="flex justify-center my-3">
                        <button className="flex items-center justify-center h-9 w-32 hover:bg-color1 rounded cursor-pointer duration-1000">
                            CONTACT
                        </button>
                    </div>
                    <div className="flex justify-center my-3">
                        <button
                            className="flex items-center justify-center h-9 w-32 hover:bg-color1 rounded cursor-pointer duration-1000"
                            onClick={() => redirect("/SignUp")}
                        >
                            SIGN UP
                        </button>
                    </div>
                    <div className="flex justify-center my-3">
                        <button
                            className="flex items-center justify-center h-9 w-32 bg-color1 rounded cursor-pointer hover:text-color4 hover:font-bold duration-1000"
                            onClick={() => redirect("/Login")}
                        >
                            LOGIN
                        </button>
                    </div>
                </div>
            )}
        </div>
    );
}
