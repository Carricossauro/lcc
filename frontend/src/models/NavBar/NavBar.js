import { React, useState } from "react";
import "./NavBar.css";

import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faBrain, faBars } from "@fortawesome/free-solid-svg-icons";

export default function NavBar() {
    const [expanded, setExpanded] = useState(false);

    const changeExpanded = () => {
        setExpanded((state) => {
            return !state;
        });
        console.log(expanded);
    };

    return (
        <div className="fixed top-0 left-0 h-32 lg:h-16 w-screen bg-color5 flex flex-wrap text-white">
            <div className="w-full lg:w-2/5 h-inherit flex items-center pl-2">
                <div className="w-1/2 lg:w-full flex items-center">
                    <FontAwesomeIcon icon={faBrain} className="icon" />
                    <span className="ml-2 text-[30px] titleFont font-normal">
                        Computational Mind
                    </span>
                </div>
                <div className="lg:invisible flex justify-end items-center w-1/2 lg:w-0 cursor-pointer">
                    <button onClick={changeExpanded}>
                        <FontAwesomeIcon
                            icon={faBars}
                            className="icon-bars mr-2 hover:text-color1 duration-500"
                        />
                    </button>
                </div>
            </div>
            <div className="w-full lg:w-3/5 h-inherit flex flex-wrap justify-center lg:justify-end items-center">
                <div className="flex justify-center mx-3">
                    <button className="flex items-center justify-center px-5 h-9 hover:bg-color1 rounded cursor-pointer duration-1000">
                        ABOUT US
                    </button>
                </div>
                <div className="flex justify-center mx-3">
                    <button className="flex items-center justify-center px-5 h-9 hover:bg-color1 rounded cursor-pointer duration-1000">
                        CONTACT
                    </button>
                </div>
                <div className="flex justify-center mx-3">
                    <button className="flex items-center justify-center px-5 h-9 hover:bg-color1 rounded cursor-pointer duration-1000">
                        SIGN UP
                    </button>
                </div>
                <div className="flex justify-center mx-3 mr-6">
                    <button className="flex items-center justify-center px-5 h-9 bg-color1 rounded cursor-pointer hover:text-color4 hover:font-bold duration-1000">
                        LOGIN
                    </button>
                </div>
            </div>
        </div>
    );
}
