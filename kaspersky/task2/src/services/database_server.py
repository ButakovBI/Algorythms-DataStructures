from services.base import ServiceBase
from helpers import round_up


class DatabaseServer(ServiceBase):
    def update_config(self, agents: int,
                      storage: float,
                      distributed: bool,
                      nodes: int,
                      traffic: float = None,
                      mail_traffic: float = None) -> None:

        if agents > 0:
            if distributed:
                self._replicas = max(round(agents / 15000), 1)
            else:
                self._replicas = 1
        else:
            self._replicas = 0

        self._memory = round(storage * 1.6, 3) if distributed else 100
        self._cpu = 1

        if nodes > 0:
            self._storage = round_up((0.00000002 * agents * agents + 0.00067749 * agents + 4.5) * agents / nodes, 3)
        else:
            self._storage = 0