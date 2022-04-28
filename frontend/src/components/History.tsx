import { CheckIcon, XIcon } from "@heroicons/react/outline";
import axios from "axios";
import { useEffect, useState } from "react";
import { getCookie } from "../utils/utils";
import HistoryPopup from "./HistoryPopup";

type HistoryElement = {
  listWord: string[][];
  target: string;
  hints: number[][];
  status: string;
};

export default function History() {
  const [history, setHistory] = useState<Array<HistoryElement>>([
    {
      listWord: [[""]],
      target: "",
      hints: [[0]],
      status: "",
    },
  ]);
  const [ready, setReady] = useState(false);
  useEffect(() => {
    axios
      .get("/api/history", {
        withCredentials: true,
        headers: {
          "X-CSRF-Token": getCookie("csrf_access_token")!,
        },
      })
      .then((response) => {
        setHistory(response.data.histo);
        let _popupState = [];
        for (let i = 0; i++; i < response.data.length) {
          _popupState.push(false);
        }
        setHistoOpen(_popupState);
        setReady(true);
      });
  }, []);
  const [histoOpen, setHistoOpen] = useState<boolean[]>([false]);

  function togglePopup(index: number, state: boolean) {
    let _openState = histoOpen;
    _openState[index] = true;
    setHistoOpen(_openState);
  }

  return ready ? (
    <ul>
      {history.map((game, index) => (
        <li
          className="flex items-center justify-between text-gray-200"
          key={game.target}
        >
          <div className="flex items-center justify-center">
            {game.status === "Victoire" ? (
              <CheckIcon className="w-6 h-6" />
            ) : (
              <XIcon className="w-6 h-6" />
            )}
            <span>{game.status}</span>
            <span>{game.target}</span>
          </div>

          <HistoryPopup
            listWord={game.listWord}
            hints={game.hints}
            histoOpen={histoOpen[index]}
            togglePopup={(state: boolean) => togglePopup(index, state)}
          />
        </li>
      ))}
    </ul>
  ) : (
    <></>
  );
}
